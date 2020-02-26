#include <include/AST/Expression/ASTBinaryOperator.hpp>

ASTBinaryOperator::ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op) : left(left), right(right), op(op), ASTExpression(BINARY_OP) {}

llvm::Value *ASTBinaryOperator::EmitIR(IREmitter::EmitterState &state)
{
    const std::string *ltype = left.GetType(state);
    const std::string *rtype = right.GetType(state);

    llvm::Value *l_inst = left.EmitIR(state);
    llvm::Value *r_inst = right.EmitIR(state);

    const Symbol *l_symbol = left.GetSymbol(state);
    const Symbol *r_symbol = right.GetSymbol(state);

    llvm::Value *templ;
    llvm::Value *tempr;

    if (l_symbol)
        templ = state.builder.CreateLoad(l_inst, "templ");
    else
        templ = l_inst;

    if (r_symbol)
        tempr = state.builder.CreateLoad(r_inst, "tempr");
    else
        tempr = r_inst;

    switch (op)
    {
        case ADD:
        {
            return state.builder.CreateAdd(templ, tempr);
        }
        case SUBTRACT:
        {
            return state.builder.CreateSub(templ, tempr);
        }
        case MULTIPLY:
        {
            return state.builder.CreateMul(templ, tempr);
        }
        case DIVIDE:
        {
            return state.builder.CreateSDiv(templ, tempr);
        }
        case EQUALITY:
        {
            return state.builder.CreateICmpEQ(templ, tempr);
        }
        case INEQUALITY:
        {
            return state.builder.CreateICmpNE(templ, tempr);
        }
        case LESSER:
        {
            return state.builder.CreateICmpSLT(templ, tempr);
        }
        case GREATER:
        {
            return state.builder.CreateICmpSGT(templ, tempr);
        }
        case LESSER_OR_EQUAL:
        {
            return state.builder.CreateICmpSLE(templ, tempr);
        }
        case GREATER_OR_EQUAL:
        {
            return state.builder.CreateICmpSGE(templ, tempr);
        }
    }
    return NULL;
}

const std::string *ASTBinaryOperator::GetType(IREmitter::EmitterState &state)
{
    return right.GetType(state);
}