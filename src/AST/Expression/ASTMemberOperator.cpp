#include <include/AST/Expression/ASTMemberOperator.hpp>

ASTMemberOperator::ASTMemberOperator(ASTIdentifier &id, ASTIdentifier &member, OP op) : id(&id), member_id(&member), OP(op) {}

llvm::Value *ASTMemberOperator::EmitIR(IREmitter::EmitterState &state)
{
    switch (op)
    {
        default:
            return NULL;
    }
}

const std::string *ASTMemberOperator::GetType(IREmitter::EmitterState &state)
{
    
}