#include <include/AST/Statement/ASTReturnStatement.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

ASTReturnStatement::ASTReturnStatement(ASTStatement &expr) : expr(&expr), ASTStatement(RETURN_STATEMENT) {}

const std::string * ASTReturnStatement::GetType(IREmitter::EmitterState & state)
{
	return expr->GetType(state);
}

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
			case UNARY_OP:
			{
				ASTUnaryOperator *unary_downcast = (ASTUnaryOperator*)expr.get();
				if (unary_downcast->op == ASTUnaryOperator::ARRAY_INDEX)
				{
					retval = state.builder.CreateLoad(retval, "load_gep_array_retaval");
					break;
				}
			}
        }
    }
    return state.builder.CreateRet(retval);
}
