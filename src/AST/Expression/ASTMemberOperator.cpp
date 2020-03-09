#include <include/AST/Expression/ASTMemberOperator.hpp>

ASTMemberOperator::ASTMemberOperator(ASTIdentifier &id, ASTIdentifier &member, OP op) : id(&id), member_id(&member), op(op), ASTExpression(MEMBER_OP) {}

llvm::Value *ASTMemberOperator::EmitIR(IREmitter::EmitterState &state)
{
    const Symbol *struct_symbol = state.symbolStack.GetSymbolByIdentifier(id->identifier);
    const JCType *struct_type = state.typeRegistry.GetTypeInfo(struct_symbol->type);
    switch (op)
    {
        default:
            return NULL;
        case DOT:
        {
            for (int i = 0; i < struct_type->MEMBER_NAMES.size(); i++)
            {
                if (struct_type->MEMBER_NAMES[i] == member_id->identifier)
                {
                    llvm::Value *get_element = state.builder.CreateGEP(struct_symbol->alloc_inst, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0),  llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), i) });
                    return get_element;
                }
            }
        }
    }
}

const std::string *ASTMemberOperator::GetType(IREmitter::EmitterState &state)
{
    const Symbol *struct_symbol = state.symbolStack.GetSymbolByIdentifier(id->identifier);
    const JCType *struct_type = state.typeRegistry.GetTypeInfo(struct_symbol->type);

    for (auto &member : struct_type->MEMBER_NAMES)
    {
        if (member_id->identifier == member)
        {
        }
    }

    return NULL;
}