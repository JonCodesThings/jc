#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

extern const char *yycurrentfilename;

ASTVariableAssignment::ASTVariableAssignment(ASTNode &assign_to, ASTNode &val) : assign_to(&assign_to), val(&val), ASTExpression(VARIABLE_ASSIGNMENT) {}

llvm::Value *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
    auto implicit_cast = [&state, this](std::unique_ptr<ASTNode> &node, const Symbol *symbol) -> llvm::Value*
    {
        //printf("%s\n", node->GetType(state)->c_str());
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

    const Symbol *assign_symbol = assign_to->GetSymbol(state);
    const Symbol *val_symbol = val->GetSymbol(state);

    if (assign_symbol)
    {
        if (val_symbol)
        {
            if (assign_symbol->type != val_symbol->type)
                return implicit_cast(val, assign_symbol);
            else
                return state.builder.CreateStore(state.builder.CreateLoad(val->EmitIR(state), "load_val_var_assign"), assign_symbol->alloc_inst);
        }
        else
        {
            if (*assign_to->GetType(state) != *val->GetType(state))
                return implicit_cast(val, assign_symbol);
            else
                return state.builder.CreateStore(val->EmitIR(state), assign_symbol->alloc_inst);
        }
    }
    else
    {
        llvm::Value *gep_assign = assign_to->EmitIR(state);

        if (val_symbol)
            return state.builder.CreateStore(val_symbol->alloc_inst, gep_assign);
        else
            return state.builder.CreateStore(val->EmitIR(state), gep_assign);
    }
    

    /*if (id)
    {
        Symbol *symbol = state.symbolStack.GetSymbolByIdentifier(id->identifier);
        const Symbol *node_symbol = node->GetSymbol(state);

        if (!symbol)
        {
            if (*node->GetType(state) != (*id->GetType(state)))
            {
                auto cast = ASTUnaryOperator(*node, new ASTIdentifier(symbol->type), ASTUnaryOperator::OP::CAST);
                node.release();
                auto emitted_ir = cast.EmitIR(state);
                if (!emitted_ir)
                {
                    printf("%s:%d:%d Error: types do not match for assignment (type %s expected, type %s given)\n",
                    yycurrentfilename, line_number, start_char, (*id->GetType(state)).c_str(), (*node->GetType(state)).c_str());
                    return NULL;
                }
                return state.builder.CreateStore(emitted_ir, symbol->alloc_inst);
            }
        }
        else if (symbol && node_symbol)
        {
            if (symbol->type != node_symbol->type)
                return implicit_cast(node, symbol);
        }

        if (node_symbol)
        {
            llvm::Value *temp = state.builder.CreateLoad(node_symbol->alloc_inst, "temp");
            return state.builder.CreateStore(temp, symbol->alloc_inst);
        }

        llvm::Value * v;
        if (symbol->type == *node->GetType(state) || state.typeRegistry.GetType(symbol->type) == state.typeRegistry.GetType(*node->GetType(state)))
            v = node->EmitIR(state);
        else
            return implicit_cast(node, symbol);
        

        if (v->getType() == symbol->alloc_inst->getType())
            v = state.builder.CreateLoad(v, "temp");

        return state.builder.CreateStore(v, symbol->alloc_inst);
    }
    else if (array_index)
    {
        const Symbol *node_symbol = node->GetSymbol(state);

        if (node_symbol)
        {
            llvm::Value *v = state.builder.CreateLoad(node_symbol->alloc_inst);
            llvm::Value *arr_index = array_index->EmitIR(state);
            return state.builder.CreateStore(v, arr_index);
        }

    }*/



    return NULL;
}