#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

extern const char *yycurrentfilename;

ASTVariableAssignment::ASTVariableAssignment(ASTIdentifier &id, ASTNode &node) : id(&id), node(&node), array_index(), ASTExpression(VARIABLE_ASSIGNMENT) {}

ASTVariableAssignment::ASTVariableAssignment(ASTNode &array_index, ASTNode &node) : id(), array_index(&array_index), node(&node), ASTExpression(VARIABLE_ASSIGNMENT) {}

llvm::Value *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
    if (id)
    {
        Symbol *symbol = state.frontmost->GetSymbolByIdentifier(id->identifier);
        const Symbol *node_symbol = node->GetSymbol(state);

        if (!symbol)
        {
            if (*node->GetType(state) != (*id->GetType(state)))
            {
                printf("implicit 101\n");
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
            {
                printf("%s\n", symbol->identifier.c_str());
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

        if (node_symbol)
        {
            llvm::Value *temp = state.builder.CreateLoad(node_symbol->alloc_inst, "temp");
            return state.builder.CreateStore(temp, symbol->alloc_inst);
        }

        llvm::Value * v;
        if (symbol->type == *node->GetType(state))
            v = node->EmitIR(state);
        else
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

    }
    return NULL;
}