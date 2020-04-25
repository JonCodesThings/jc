#include <include/AST/Statement/ASTReturnStatement.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

#include <include/AST/Constant/ASTConstantNullptr.hpp>

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
		if (expr->GetNodeType() == UNARY_OP)
		{
			ASTUnaryOperator *unary_downcast = (ASTUnaryOperator*)expr.get();
			if (unary_downcast->op == ASTUnaryOperator::ARRAY_INDEX)
			{
				retval = state.builder.CreateLoad(retval, "load_gep_array_retaval");
				retval = state.builder.CreateLoad(retval, "load_gep_array_retaval");
			}
			return state.builder.CreateRet(retval);
		}
		else
		{
			retval = state.builder.CreateLoad(retval, "load_retaval");
			return state.builder.CreateRet(retval);
		}
	}
	//otherwise emit the IR and depending on the node type do different things
    else
    {
		if (expr->GetNodeType() == NULLPTR)
		{
			ASTConstantNullptr *np = (ASTConstantNullptr*)expr.get();
			np->nullptr_type = (llvm::PointerType*)current_function->getReturnType();
		}
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
				break;
			}
        }
    }
    return state.builder.CreateRet(retval);
}

const bool ASTReturnStatement::SyntheticEval(IREmitter::EmitterState & state)
{
	return expr->SyntheticEval(state);
}
