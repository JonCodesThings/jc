#include <include/AST/Statement/ASTReturnStatement.hpp>

ASTReturnStatement::ASTReturnStatement(ASTStatement &expr) : expr(&expr), ASTStatement(RETURN_STATEMENT) {}

llvm::Value *ASTReturnStatement::EmitIR(IREmitter::EmitterState &state)
{
	//variable to store the retval in
    llvm::Value *retval;

	//if the expression has a symbol get it by emitting the IR and loading the result
    if (expr->GetSymbol(state))
    {
        retval = expr->EmitIR(state);
        retval = state.builder.CreateLoad(retval);
    }
	//otherwise emit the IR and depending on the node type do different things
    else
    {
        retval = expr->EmitIR(state);
        switch (expr->GetNodeType())
        {
            default:
            break;
            case MEMBER_OP:
                retval = state.builder.CreateLoad(retval, "load_gep_retval");
                break;
        }
    }
    return state.builder.CreateRet(retval);
}
