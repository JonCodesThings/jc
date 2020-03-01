#include <include/AST/Constant/ASTConstantString.hpp>

const std::string PreProcess(std::string s)
{
    std::string n;
    for (auto it = s.begin(); it != s.end(); it++)
    {
        if ((*it) == '\\')
        {
            auto next = std::next(it);
            if (next != s.end())
            {
                switch (*next)
                {
                    default:
                        break;
                    case 'n':
                    {
                        n.push_back('\n');
                        it++;
                        break;
                    }
                    case 't':
                    {
                        n.push_back('\t');
                        it++;
                        break;
                    }
                }
            }
        }
        else
        {
            n.push_back(*it);
        }
    }
    return n;
}

ASTConstantString::ASTConstantString(const std::string &constant) : constant(PreProcess(constant.substr(1, constant.size() - 2))) {}

llvm::Value *ASTConstantString::EmitIR(IREmitter::EmitterState &state) 
{ 
    return state.builder.CreateGlobalStringPtr(constant); 
}

const std::string *ASTConstantString::GetType(IREmitter::EmitterState &state)
{
    return state.typeRegistry.GetLifetimeTypeString("void");
}