#include <include/AST/Expression/ASTUnaryOperator.hpp>

ASTUnaryOperator::ASTUnaryOperator(ASTNode &operatee, OP op) : operatee(operatee), cast(NULL), index(NULL), op(op), ASTExpression(UNARY_OP) {}

ASTUnaryOperator::ASTUnaryOperator(ASTNode &operatee, ASTIdentifier *identifier, OP op) : operatee(operatee), cast(identifier), index(NULL), op(op), ASTExpression(UNARY_OP) {}

ASTUnaryOperator::ASTUnaryOperator(ASTNode &operatee, ASTConstantInt &index, OP op) : operatee(operatee), cast(NULL), index(&index), op(op), ASTExpression(UNARY_OP) {}

llvm::Value *ASTUnaryOperator::EmitIR(IREmitter::EmitterState &state)
{
    const std::string *type = operatee.GetType(state);
    const Symbol *s = operatee.GetSymbol(state);

    switch (op)
    {
        default:
            return NULL;
        case ADDRESS_OF:
        {
            return s->alloc_inst;
        }
        case DEREFERENCE:
        {
            llvm::Value *v = state.builder.CreateLoad(s->alloc_inst, "temp_deref");
            return state.builder.CreateLoad(v);
        }
        case ARRAY_INDEX:
        {
            if (!cast)
                return state.builder.CreateGEP(s->alloc_inst, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0), index->EmitIR(state) });

            Symbol *cs = state.frontmost->GetSymbolByIdentifier(cast->identifier);

            llvm::Value *v  = state.builder.CreateLoad(cs->alloc_inst, "temp");

            if (v->getType() == llvm::Type::getInt32Ty(state.context))
                v = state.builder.CreateGEP(s->alloc_inst, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0), v});
            return v;
        }
        case CAST:
        {
            const std::string *cast_to = cast->GetType(state);

            if (state.typeRegistry.IsTypeNumeric(*type) && state.typeRegistry.IsTypeNumeric(*cast_to))
            {
                llvm::Type *conver = state.typeRegistry.GetNarrowingConversion(*type, *cast_to);

                if (!conver)
                    conver = state.typeRegistry.GetWideningConversion(*type, *cast_to);

                if (!conver)
                    return NULL;

                llvm::Value *v = operatee.EmitIR(state);

                if (s)
                    v = state.builder.CreateLoad(s->alloc_inst, "temp");


                //TODO: allow this to support unsigned types

                JCType::TYPE_CLASSIFICATION t = state.typeRegistry.GetTypeInfo(*cast_to)->classification;
                JCType::TYPE_CLASSIFICATION f = state.typeRegistry.GetTypeInfo(*type)->classification;

                if (f == JCType::TYPE_CLASSIFICATION::FLOAT && t == JCType::TYPE_CLASSIFICATION::FLOAT)
                    return state.builder.CreateFPCast(v, conver);
                if (f == JCType::TYPE_CLASSIFICATION::INT && t == JCType::TYPE_CLASSIFICATION::INT)
                    return state.builder.CreateIntCast(v, conver, true);
                if (f == JCType::TYPE_CLASSIFICATION::FLOAT && t == JCType::TYPE_CLASSIFICATION::INT)
                    return state.builder.CreateFPToSI(v, conver);
                if (f == JCType::TYPE_CLASSIFICATION::INT && t == JCType::TYPE_CLASSIFICATION::FLOAT)
                    return state.builder.CreateSIToFP(v, conver);
                return NULL;
            }

        }
        case INCREMENT:
        {
            llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
            llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(state.typeRegistry.GetType(*type), 1));
            return state.builder.CreateStore(added, s->alloc_inst);
        }
        case DECREMENT:
        {
            llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
            llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(state.typeRegistry.GetType(*type), 1));
            return state.builder.CreateStore(added, s->alloc_inst);
        }
    }
    return NULL;
}