#include <include/AST/Statement/ASTDeferredStatement.hpp>

  
ASTDeferredStatement::ASTDeferredStatement(ASTStatement &defer) : defer(defer), ASTStatement(DEFER_STATEMENT) {}

llvm::Value *ASTDeferredStatement::EmitIR(IREmitter::EmitterState &state)
{
    return NULL;
}