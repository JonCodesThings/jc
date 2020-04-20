#include <include/AST/Expression/ASTUnaryOperator.hpp>

#include <include/AST/Constant/ASTConstantFloat.hpp>

ASTUnaryOperator::ASTUnaryOperator(ASTNode &operatee, OP op) : operatee(&operatee), cast(), index(), op(op), ASTExpression(UNARY_OP) {}

ASTUnaryOperator::ASTUnaryOperator(ASTNode &operatee, ASTIdentifier *identifier, OP op) : operatee(&operatee), cast(identifier), index(), op(op), ASTExpression(UNARY_OP) {}

ASTUnaryOperator::ASTUnaryOperator(ASTNode &operatee, ASTConstantInt &index, OP op) : operatee(&operatee), cast(), index(&index), op(op), ASTExpression(UNARY_OP) {}

llvm::Value *ASTUnaryOperator::EmitIR(IREmitter::EmitterState &state)
{
	//get the type string pointer and symbol of the node being operated on
    const std::string *type = operatee->GetType(state);
    const Symbol *s = operatee->GetSymbol(state);

	//do different things based on the op
    switch (op)
    {
        default:
            return nullptr;
        case ADDRESS_OF:
        {
			if (s->classification == Symbol::Classification::FUNCTION)
			{
				return s->function;
			}
			else if (s->classification == Symbol::Classification::VARIABLE)
			{
				return s->alloc_inst;
			}
        }
        case DEREFERENCE:
        {
            llvm::Value *v = state.builder.CreateLoad(s->alloc_inst, "temp_deref");
            return state.builder.CreateLoad(v);
        }
        case ARRAY_INDEX:
        {
			//if there is nothing in the identifier variable then we use GEP
            if (!cast)
                return state.builder.CreateGEP(s->alloc_inst, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0), index->EmitIR(state) });

			//otherwise we get the symbol, load it and then use GEP

            Symbol *cs = state.symbolStack.GetSymbolByIdentifier(cast->identifier);

            llvm::Value *v  = state.builder.CreateLoad(cs->alloc_inst, "temp");

			//TODO: fix this awful hack
            if (v->getType() == llvm::Type::getInt32Ty(state.context))
                v = state.builder.CreateGEP(s->alloc_inst, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0), v});

            return v;
        }
        case CAST:
        {
			//find out what we're casting to
            const std::string *cast_to = cast->GetType(state);

			//do the conversion and then do the correct cast
            if (state.typeRegistry.IsTypeNumeric(*type) && state.typeRegistry.IsTypeNumeric(*cast_to))
            {
                llvm::Type *conver = state.typeRegistry.GetNarrowingConversion(*type, *cast_to);

                if (!conver)
                    conver = state.typeRegistry.GetWideningConversion(*type, *cast_to);

                if (!conver)
                    return nullptr;

                llvm::Value *v = operatee->EmitIR(state);

                if (s)
                    v = state.builder.CreateLoad(s->alloc_inst, "temp");

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
                return nullptr;
            }
            return nullptr;
        }
		//increment
		//TODO: allow this to support other types
        case INCREMENT:
        {
			if (s->assigned && !s->mut)
			{
				printf("Error in module %s line %d: cannot assign new value to non-mutable variable %s.\n", state.module_name.c_str(), line_number, s->identifier);
				return nullptr;
			}
            llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
            llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(state.typeRegistry.GetType(*type), 1));
            state.builder.CreateStore(added, s->alloc_inst);
			return state.builder.CreateLoad(s->alloc_inst, "temp");
        }
		//decrement
		//TODO: allow this to support other types
        case DECREMENT:
        {
			if (s->assigned && !s->mut)
			{
				printf("Error in module %s line %d: cannot assign new value to non-mutable variable %s.\n", state.module_name.c_str(), line_number, s->identifier);
				return nullptr;
			}
            llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
            llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(state.typeRegistry.GetType(*type), 1));
            state.builder.CreateStore(added, s->alloc_inst);
			return state.builder.CreateLoad(s->alloc_inst, "temp");
        }
		case MINUS:
		case PLUS:
		{
			if (type)
			{
				if (!state.typeRegistry.IsTypeNumeric(*type))
				{
					printf("Error in module %s line %d: cannot use unary plus/minus on non-numeric variable %s.\n", state.module_name.c_str(), line_number, s->identifier);
					return nullptr;
				}
			}
			if (s)
			{
				llvm::Value *v = state.builder.CreateLoad(s->alloc_inst);
				const JCType *tinfo = state.typeRegistry.GetTypeInfo(s->type);

				if (tinfo->classification == JCType::TYPE_CLASSIFICATION::INT)
					v = state.builder.CreateSub(llvm::ConstantInt::get(tinfo->llvm_type, 0), v);
				else if (tinfo->classification == JCType::TYPE_CLASSIFICATION::FLOAT)
					v = state.builder.CreateSub(llvm::ConstantFP::get(tinfo->llvm_type, 0.0f), v);
				else
					v = nullptr;

				return v;
			}
			switch (operatee->GetNodeType())
			{
			case CONSTANT:
			{
				if (*type == "i32")
				{
					ASTConstantInt *downcast = (ASTConstantInt*)operatee.get();
					if (op == PLUS)
						downcast->constant = +downcast->constant;
					else
						downcast->constant = -downcast->constant;

				}
				else
				{
					ASTConstantFloat *downcast = (ASTConstantFloat*)operatee.get();
					if (op == PLUS)
						downcast->constant = +downcast->constant;
					else
						downcast->constant = -downcast->constant;
				}
				return operatee->EmitIR(state);

			}
			}
		}
    }
    return nullptr;
}

const std::string *ASTUnaryOperator::GetType(IREmitter::EmitterState &state)
{
    //TODO: Jon
    //get the type stuff working for more types of unary operators
    const Symbol *s = operatee->GetSymbol(state);

	if (s == nullptr)
	{
		operatee->SyntheticEval(state);
		s = operatee->GetSymbol(state);
	}

    switch (op)
    {
        default:
            return nullptr;
        case INCREMENT:
        case DECREMENT:
            return state.typeRegistry.GetLifetimeTypeString(s->type);
        case CAST:
            return cast->GetType(state);
        case ADDRESS_OF:
        {
            std::string pointer_ty = s->type + "*";
            const std::string *exists = state.typeRegistry.GetLifetimeTypeString(pointer_ty);

			if (s->classification == Symbol::FUNCTION)
			{
				return state.typeRegistry.GetLifetimeTypeString(*s->function->getFunctionType());
			}
			else if (s->classification == Symbol::VARIABLE)
			{
				if (!exists)
				{
					llvm::Type *t = state.typeRegistry.UnwindPointerType(pointer_ty);
					state.typeRegistry.AddType(pointer_ty, *t, JCType::TYPE_CLASSIFICATION::POINTER);
				}
			}
            return state.typeRegistry.GetLifetimeTypeString(pointer_ty);
        }
        case ARRAY_INDEX:
            return state.typeRegistry.GetLifetimeTypeString(s->type);
		case MINUS:
		case PLUS:
			return operatee->GetType(state);
    }
}

const Symbol * ASTUnaryOperator::GetSymbol(IREmitter::EmitterState & state)
{
	return operatee->GetSymbol(state);
}

const bool ASTUnaryOperator::SyntheticEval(IREmitter::EmitterState &state)
{
	return operatee->SyntheticEval(state);
}