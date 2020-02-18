#include <include/AST/Statement/ASTReturnStatement.hpp>

ASTReturnStatement::ASTReturnStatement(ASTStatement &expr) : expr(&expr) {}

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
    return state.builder.CreateRet(retval);
}
