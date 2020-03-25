#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

extern const char *yycurrentfilename;

ASTVariableAssignment::ASTVariableAssignment(ASTNode &assign_to, ASTNode &val) : assign_to(&assign_to), val(&val), ASTExpression(VARIABLE_ASSIGNMENT) {}

llvm::Value *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
	//handy lambda for doing implicit casting
    auto implicit_cast = [&state, this](std::unique_ptr<ASTNode> &node, const Symbol *symbol) -> llvm::Value*
    {
        std::unique_ptr<ASTUnaryOperator> cast;

        if (!state.typeRegistry.IsTypeNumeric(*node->GetType(state)))
            return NULL;

        if (!state.typeRegistry.IsTypeNumeric(symbol->type))
            return NULL;
        
        if (symbol)
            cast = std::make_unique<ASTUnaryOperator>(*node, new ASTIdentifier(symbol->type), ASTUnaryOperator::OP::CAST);
            
        else
            cast = std::make_unique<ASTUnaryOperator>(*node, new ASTIdentifier(*val->GetType(state)), ASTUnaryOperator::OP::CAST);
        node.release();
        auto emitted_ir = cast->EmitIR(state);
        if (!emitted_ir)
        {
                printf("%s:%d:%d Error: types do not match for assignment (type %s expected, type %s given)\n",
                yycurrentfilename, line_number, start_char, (*assign_to->GetType(state)).c_str(), (*node->GetType(state)).c_str());
                return NULL;
        }
        if (symbol)
            return state.builder.CreateStore(emitted_ir, symbol->alloc_inst);
        else
            return NULL;
    };

	//get the assigning and assigned value symbols
    const Symbol *assign_symbol = assign_to->GetSymbol(state);
    const Symbol *val_symbol = val->GetSymbol(state);

	//if the assigned symbol exists
    if (assign_symbol)
    {
		//if the value symbol exists
        if (val_symbol)
        {
			//perform an implicit cast as required or just emit store operation
            if (assign_symbol->type != val_symbol->type)
                return implicit_cast(val, assign_symbol);
            else
                return state.builder.CreateStore(state.builder.CreateLoad(val->EmitIR(state), "load_val_var_assign"), assign_symbol->alloc_inst);
        }
		//otherwise
        else
        {
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
						store = state.builder.CreateLoad(store, "load_val_to_store");
						break;
					}   
                }
                else if (val->GetNodeType() == MEMBER_OP)
                    store = state.builder.CreateLoad(store, "load_val_to_store");

				//return a store operation
				state.module->print(llvm::errs(), nullptr);
				return state.builder.CreateStore(store, assign_symbol->alloc_inst);
            }
        }
    }
	//otherwise
    else
    {
		//emit the IR for gep assignment
        llvm::Value *gep_assign = assign_to->EmitIR(state);
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
    return NULL;
}