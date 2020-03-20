#include <include/AST/Expression/ASTBinaryOperator.hpp>

ASTBinaryOperator::ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op) : left(&left), right(&right), op(op), ASTExpression(BINARY_OP) {}

llvm::Value *ASTBinaryOperator::EmitIR(IREmitter::EmitterState &state)
{
	//retrieve type strings
    const std::string *ltype = left->GetType(state);
    const std::string *rtype = right->GetType(state);

	//get evaluations of left and right nodes
    llvm::Value *l_inst = left->EmitIR(state);
    llvm::Value *r_inst = right->EmitIR(state);

	//retrieve symobls for each
    const Symbol *l_symbol = left->GetSymbol(state);
    const Symbol *r_symbol = right->GetSymbol(state);

	//use these variables to store either the returned value above or create a load as required
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

	// perform the operation
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
            if ((*ltype)[0] == 'u')
                return state.builder.CreateUDiv(templ, tempr);
            else
                return state.builder.CreateSDiv(templ, tempr);
        }
        case EQUALITY:
        {
            switch (state.typeRegistry.GetTypeInfo(*ltype)->classification)
            {
                default:
                    return NULL;
                case JCType::TYPE_CLASSIFICATION::INT:
                    return state.builder.CreateICmpEQ(templ, tempr);
                case JCType::TYPE_CLASSIFICATION::FLOAT:
                    return state.builder.CreateFCmpOEQ(templ, tempr);
            }
        }
        case INEQUALITY:
        {
            switch (state.typeRegistry.GetTypeInfo(*ltype)->classification)
            {
                default:
                    return NULL;
                case JCType::TYPE_CLASSIFICATION::INT:
                    return state.builder.CreateICmpNE(templ, tempr);
                case JCType::TYPE_CLASSIFICATION::FLOAT:
                    return state.builder.CreateFCmpONE(templ, tempr);
            }
        }
        case LESSER:
        {
            switch (state.typeRegistry.GetTypeInfo(*ltype)->classification)
            {
                default:
                    return NULL;
                case JCType::TYPE_CLASSIFICATION::INT:
                    return state.builder.CreateICmpSLT(templ, tempr);
                case JCType::TYPE_CLASSIFICATION::FLOAT:
                    return state.builder.CreateFCmpOLT(templ, tempr);
            }
        }
        case GREATER:
        {
            switch (state.typeRegistry.GetTypeInfo(*ltype)->classification)
            {
                default:
                    return NULL;
                case JCType::TYPE_CLASSIFICATION::INT:
                    return state.builder.CreateICmpSGT(templ, tempr);
                case JCType::TYPE_CLASSIFICATION::FLOAT:
                    return state.builder.CreateFCmpOGT(templ, tempr);
            }
        }
        case LESSER_OR_EQUAL:
        {
            switch (state.typeRegistry.GetTypeInfo(*ltype)->classification)
            {
                default:
                    return NULL;
                case JCType::TYPE_CLASSIFICATION::INT:
                    return state.builder.CreateICmpSLE(templ, tempr);
                case JCType::TYPE_CLASSIFICATION::FLOAT:
                    return state.builder.CreateFCmpOLE(templ, tempr);
            }
        }
        case GREATER_OR_EQUAL:
        {
            switch (state.typeRegistry.GetTypeInfo(*ltype)->classification)
            {
                default:
                    return NULL;
                case JCType::TYPE_CLASSIFICATION::INT:
                    return state.builder.CreateICmpSGE(templ, tempr);
                case JCType::TYPE_CLASSIFICATION::FLOAT:
                    return state.builder.CreateFCmpOGE(templ, tempr);
            }
        }
    }
    return NULL;
}

const std::string *ASTBinaryOperator::GetType(IREmitter::EmitterState &state)
{
    return right->GetType(state);
}