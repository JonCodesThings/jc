#include <include/AST/Statement/ASTReturnStatement.hpp>

ASTReturnStatement::ASTReturnStatement(ASTStatement &expr) : expr(&expr), ASTStatement(RETURN_STATEMENT) {}

llvm::Value *ASTReturnStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::Value *retval;
    if (expr->GetSymbol(state))
    {
        retval = expr->EmitIR(state);
        retval = state.builder.CreateLoad(retval);
    }
    else
        retval = expr->EmitIR(state);
    prev_processed = node_type;
    return state.builder.CreateRet(retval);
}
