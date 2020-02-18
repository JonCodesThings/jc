#include <include/AST/Constant/ASTConstantString.hpp>

ASTConstantString::ASTConstantString(const std::string &constant) : constant(constant.substr(1, constant.size() - 2)) {}

llvm::Value *ASTConstantString::EmitIR(IREmitter::EmitterState &state) 
{ 
    return state.builder.CreateGlobalStringPtr(constant); 
}

const std::string *ASTConstantString::GetType(IREmitter::EmitterState &state)
{
    return state.typeRegistry.GetLifetimeTypeString("void");
}