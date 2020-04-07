#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

#include <include/AST/Constant/ASTConstantNullptr.hpp>

extern const char *yycurrentfilename;

ASTVariableAssignment::ASTVariableAssignment(ASTNode &assign_to, ASTNode &val) : assign_to(&assign_to), val(&val), ASTExpression(VARIABLE_ASSIGNMENT) {}

llvm::Value *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
	//handy lambda for doing implicit casting
    auto implicit_cast = [&state, this](std::unique_ptr<ASTNode> &node, const Symbol *symbol) -> llvm::Value*
    {
        std::unique_ptr<ASTUnaryOperator> cast;

        if (!state.typeRegistry.IsTypeNumeric(*node->GetType(state)))
            return nullptr;

        if (!state.typeRegistry.IsTypeNumeric(symbol->type))
            return nullptr;
        
        if (symbol)
            cast = std::make_unique<ASTUnaryOperator>(*node.release(), new ASTIdentifier(symbol->type), ASTUnaryOperator::OP::CAST);
        else
            cast = std::make_unique<ASTUnaryOperator>(*node.release(), new ASTIdentifier(*val->GetType(state)), ASTUnaryOperator::OP::CAST);
        auto emitted_ir = cast->EmitIR(state);
        if (!emitted_ir)
        {
                printf("Error in module %s line %d: types do not match for assignment (type %s expected, type %s given)\n",
                yycurrentfilename, line_number, (*assign_to->GetType(state)).c_str(), (*node->GetType(state)).c_str());
                return nullptr;
        }
        if (symbol)
            return state.builder.CreateStore(emitted_ir, symbol->alloc_inst);
        else
            return nullptr;
    };

	//get the assigning and assigned value symbols
    const Symbol *assign_symbol = assign_to->GetSymbol(state);
    const Symbol *val_symbol = val->GetSymbol(state);

	if (val->GetNodeType() == NULLPTR)
	{
		ASTConstantNullptr *np = (ASTConstantNullptr*)val.get();
		np->nullptr_type = (llvm::PointerType*)state.typeRegistry.GetType(*assign_to->GetType(state));
		np->nullptrtype_str = state.typeRegistry.GetLifetimeTypeString(*assign_to->GetType(state));
	}

	//if the assigned symbol exists
    if (assign_symbol)
    {
		if (assign_symbol->array_size == 1)
		{
			auto is_assigned_symbol = const_cast<Symbol*>(assign_symbol);
			bool mut_flag;

			if (assign_symbol->full_type.find('*') != std::string::npos)
				mut_flag = assign_symbol->ptr_mut;
			else
				mut_flag = assign_symbol->mut;

			if (!mut_flag && assign_symbol->assigned)
			{
				printf("Error in module %s line %d: cannot assign new value to non-mutable variable %s.\n", state.module_name.c_str(), line_number, assign_symbol->identifier);
				return nullptr;
			}
			//if the value symbol exists
			if (val_symbol)
			{
				if (val->GetNodeType() == UNARY_OP)
				{
					ASTUnaryOperator *downcast = (ASTUnaryOperator*)val.get();
					switch (downcast->op)
					{
					default:
						break;
					case ASTUnaryOperator::ADDRESS_OF:
					{
						llvm::Value *v = state.builder.CreateStore(val->EmitIR(state), assign_symbol->alloc_inst);
						return v;
					}
					case ASTUnaryOperator::INCREMENT:
					case ASTUnaryOperator::DECREMENT:
					{
						llvm::Value *v = state.builder.CreateStore(val->EmitIR(state), assign_symbol->alloc_inst);
						return v;
					}
					}
				}
				else if (val->GetNodeType() == MEMBER_OP)
				{
					llvm::Value *store = state.builder.CreateLoad(val->EmitIR(state), "load_val_to_store");
					return state.builder.CreateStore(store, assign_symbol->alloc_inst);
				}
				is_assigned_symbol->assigned = true;
				//perform an implicit cast as required or just emit store operation
				if (assign_symbol->type != val_symbol->type)
					return implicit_cast(val, assign_symbol);
				else
					return state.builder.CreateStore(state.builder.CreateLoad(val->EmitIR(state), "load_val_var_assign"), assign_symbol->alloc_inst);
			}
			//otherwise
			else
			{
				is_assigned_symbol->assigned = true;
				//perform an implicit cast if required
				if (assign_to->GetType(state) != val->GetType(state))
					return implicit_cast(val, assign_symbol);
				else
				{
					//otherwise do a whole load of hacks to ensure the correct value is loaded
					llvm::Value *store = val->EmitIR(state);
					if (val->GetNodeType() == UNARY_OP)
					{
						ASTUnaryOperator *cast_down = (ASTUnaryOperator*)val.get();
						switch (cast_down->op)
						{
						default:
							break;
						case ASTUnaryOperator::OP::ARRAY_INDEX:
						{
							store = state.builder.CreateLoad(store, "load_val_to_store");
							break;
						}

						}
					}
					else if (val->GetNodeType() == MEMBER_OP)
						store = state.builder.CreateLoad(store, "load_val_to_store");

					llvm::Value *v = assign_symbol->alloc_inst;
					if (assign_to->GetNodeType() == MEMBER_OP)
					{
						v = assign_to->EmitIR(state);
					}

					//return a store operation
					return state.builder.CreateStore(store, v);
				}
			}
		}
		//otherwise
		else
		{
			//emit the IR for gep assignment
			llvm::Value *gep_assign = assign_to->EmitIR(state);
			if (!assign_to->GetSymbol(state)->ptr_mut)
			{
				printf("Error in module %s line %d: cannot assign new value to non-mutable variable %s.\n", state.module_name.c_str(), line_number, assign_symbol->identifier);
				return nullptr;
			}
			//if there is a value symbol load it and then store it
			if (val_symbol)
			{
				llvm::Value *val_load = state.builder.CreateLoad(val->EmitIR(state), "load_val_var_assign_val");
				return state.builder.CreateStore(val_load, gep_assign);
			}
			//otherwise just do a straight store
			else
				return state.builder.CreateStore(val->EmitIR(state), gep_assign);
		}
    }
    return nullptr;
}