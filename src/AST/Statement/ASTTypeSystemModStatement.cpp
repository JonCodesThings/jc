#include <include/AST/Statement/ASTTypeSystemModStatement.hpp>

ASTTypeSystemModStatement::ASTTypeSystemModStatement(const TYPE_MOD_OP &op) : op(op), ASTStatement(TYPE_MOD) {}

llvm::Value *ASTTypeSystemModStatement::EmitIR(IREmitter::EmitterState &state)
{
    return NULL;
}