#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

#include <include/AST/Constant/ASTConstantNullptr.hpp>

extern const char *yycurrentfilename;

ASTVariableAssignment::ASTVariableAssignment(ASTNode &assign_to, ASTNode &val) : assign_to(&assign_to), val(&val), ASTExpression(VARIABLE_ASSIGNMENT) {}

llvm::Value *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
	//handy lambda for doing implicit casting
    auto implicit_cast = [&state, this](std::unique_ptr<ASTNode> &node, const Symbol *store_at_symbol) -> llvm::Value*
    {
        std::unique_ptr<ASTUnaryOperator> cast;

        if (!state.typeRegistry.IsTypeNumeric(*node->GetType(state)))
            return nullptr;

		if (!state.typeRegistry.IsTypeNumeric(store_at_symbol->type))
			return nullptr;
        
        if (store_at_symbol)
            cast = std::make_unique<ASTUnaryOperator>(*node.release(), new ASTIdentifier(store_at_symbol->type), ASTUnaryOperator::OP::CAST);
        else
            cast = std::make_unique<ASTUnaryOperator>(*node.release(), new ASTIdentifier(*val->GetType(state)), ASTUnaryOperator::OP::CAST);
        auto emitted_ir = cast->EmitIR(state);
        if (!emitted_ir)
        {
                printf("Error in module %s line %d: types do not match for assignment (type %s expected, type %s given)\n",
                yycurrentfilename, line_number, (*assign_to->GetType(state)).c_str(), (*node->GetType(state)).c_str());
                return nullptr;
        }
        if (store_at_symbol)
			return state.builder.CreateStore(emitted_ir, store_at_symbol->alloc_inst);
        else
            return nullptr;
    };

	llvm::Value *store_at = nullptr;
	llvm::Value *actual_value = nullptr;

	switch (assign_to->GetNodeType())
	{
	default:
		printf("Error in module %s on line %d: cannot assign value to this kind of expression.\n", state.module_name.c_str(), line_number);
		return nullptr;
	case IDENTIFIER:
	{
		store_at = assign_to->EmitIR(state);
		break;
	}
	case MEMBER_OP:
	{
		//@Jon
		//TODO: implement this!
		store_at = assign_to->EmitIR(state);
		break;
	}
	case UNARY_OP:
	{
		ASTUnaryOperator *downcast = (ASTUnaryOperator*)assign_to.get();
		switch (downcast->op)
		{
		default:
			printf("Error in module %s on line %d: cannot assign value to this kind of unary operator.\n", state.module_name.c_str(), line_number);
			return nullptr;
		case ASTUnaryOperator::OP::DEREFERENCE:
		{
			store_at = assign_to->EmitIR(state);
			break;
		}
		case ASTUnaryOperator::OP::ARRAY_INDEX:
		{
			store_at = downcast->EmitIR(state);
			//store_at = state.builder.CreateLoad(store_at, "get_assign_to_gep_load");
			break;
		}
		}
		break;
	}
	}

	switch (val->GetNodeType())
	{
	default:
		printf("Error in module %s on line %d: cannot assign this value to a variable.\n", state.module_name.c_str(), line_number);
		return nullptr;
	case CONSTANT:
	{
		actual_value = val->EmitIR(state);
		break;
	}
	case IDENTIFIER:
	{
		actual_value = val->EmitIR(state);
		actual_value = state.builder.CreateLoad(actual_value, "load_val_from_identifier");
		break;
	}
	case MEMBER_OP:
	{
		//@Jon
		//TODO: implement this!
		actual_value = assign_to->EmitIR(state);
		actual_value = state.builder.CreateLoad(actual_value, "load_val_from_gep_member_op");
		break;
	}
	case UNARY_OP:
	{
		ASTUnaryOperator *downcast = (ASTUnaryOperator*)val.get();
		switch (downcast->op)
		{
		default:
			printf("Error in module %s on line %d: cannot assign value from this kind of unary operator.\n", state.module_name.c_str(), line_number);
			return nullptr;
		case ASTUnaryOperator::CAST:
		case ASTUnaryOperator::ADDRESS_OF:
		{
			actual_value = val->EmitIR(state);
			break;
		}
		case ASTUnaryOperator::INCREMENT:
		case ASTUnaryOperator::DECREMENT:
		case ASTUnaryOperator::DEREFERENCE:
		{
			actual_value = val->EmitIR(state);
			actual_value = state.builder.CreateLoad(actual_value, "load_val_from_unary_op");
			break;
		}
		case ASTUnaryOperator::ARRAY_INDEX:
		{
			actual_value = val->EmitIR(state);
			actual_value = state.builder.CreateLoad(actual_value, "load_gep_from_unary_op");
			//actual_value = state.builder.CreateLoad(actual_value, "load_val_from_unary_op_");
			break;
		}
		}
		break;
	}
	case BINARY_OP:
	{
		actual_value = val->EmitIR(state);
		break;
	}
	case NULLPTR:
	{
		ASTConstantNullptr *np = (ASTConstantNullptr*)val.get();
		np->nullptr_type = (llvm::PointerType*)state.typeRegistry.GetType(*assign_to->GetType(state));
		np->nullptrtype_str = state.typeRegistry.GetLifetimeTypeString(*assign_to->GetType(state));
		actual_value = np->EmitIR(state);
	}
	case FUNCTION_CALL:
	{
		actual_value = val->EmitIR(state);
		break;
	}
	}

	//get the assigning and assigned value symbols
    const Symbol *assign_symbol = assign_to->GetSymbol(state);
    const Symbol *val_symbol = val->GetSymbol(state);

	if (assign_to->GetType(state) == val->GetType(state))
		return state.builder.CreateStore(actual_value, store_at);
	else
	{
		if (val->GetNodeType() == UNARY_OP || assign_to->GetNodeType() == MEMBER_OP)
		{
			return state.builder.CreateStore(actual_value, store_at);
		}
		else
			return implicit_cast(val, assign_symbol);
	}

    return nullptr;
}