#include <include/AST/Expression/ASTMemberOperator.hpp>

ASTMemberOperator::ASTMemberOperator(ASTNode &id, ASTNode &member, OP op) : id(&id), member(&member), op(op), ASTExpression(MEMBER_OP) 
{

}

llvm::Value *ASTMemberOperator::EmitIR(IREmitter::EmitterState &state)
{
	//get the struct's symbol and type
	ASTIdentifier *inode = nullptr;
	ASTMemberOperator *mnode = nullptr;

	if (id->GetNodeType() == IDENTIFIER)
		inode = (ASTIdentifier*)id.get();
	if (id->GetNodeType() == UNARY_OP)
		base_ptr = id->EmitIR(state);

	if (member->GetNodeType() == MEMBER_OP)
		mnode = (ASTMemberOperator*)member.get();
		

    const Symbol *symbol = id->GetSymbol(state);

	const JCType *type = nullptr;
	if (symbol)
		type = state.typeRegistry.GetTypeInfo(symbol->type);

	


	if (!base_ptr)
		base_ptr = symbol->alloc_inst;
	else if (base_ptr && base_struct_typeinfo)
		type = base_struct_typeinfo;
	else
		type = state.typeRegistry.GetTypeInfo(symbol->type.substr(0, symbol->type.length() - 1));

	//based on the operator do different things
	//TODO: add the arrow operator for pointers

	//state.module->print(llvm::errs(), nullptr);
    switch (op)
    {
        default:
            return nullptr;
        case DOT:
        {
			if (member->GetNodeType() == IDENTIFIER)
			{
				//get the element using GEP if possible
				for (int i = 0; i < type->MEMBER_NAMES.size(); i++)
				{
					ASTIdentifier *m = (ASTIdentifier*)member.get();
					if (type->MEMBER_NAMES[i] == m->identifier)
					{
						if (type->classification == JCType::TYPE_CLASSIFICATION::STRUCT)
						{
							llvm::Value *get_element = state.builder.CreateGEP(state.typeRegistry.GetType(type->MEMBER_TYPENAMES[i]), base_ptr, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), i) });
							return get_element;
						}
						else if (type->classification == JCType::TYPE_CLASSIFICATION::UNION)
						{
							llvm::Value *get_element = state.builder.CreateGEP(base_ptr, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0),  llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0) });
							llvm::Value *get_union_element = state.builder.CreateBitCast(get_element, state.typeRegistry.GetType(type->MEMBER_TYPENAMES[i] + "*"));
							return get_union_element;
						}
					}
				}
			}
			else if (mnode)
			{
				ASTIdentifier *idet = (ASTIdentifier*)mnode->id.get();
				std::string id = idet->identifier;
				//get the element using GEP if possible
				for (int i = 0; i < type->MEMBER_NAMES.size(); i++)
				{
					if (type->MEMBER_NAMES[i] == id)
					{
						if (type->classification == JCType::TYPE_CLASSIFICATION::STRUCT)
						{
							llvm::Value *get_element = state.builder.CreateGEP(state.typeRegistry.GetType(type->MEMBER_TYPENAMES[i]), base_ptr, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), i) });
							mnode->base_ptr = get_element;
							mnode->base_struct_typeinfo = state.typeRegistry.GetTypeInfo(type->MEMBER_TYPENAMES[i]);
							return mnode->EmitIR(state);
						}
						else if (type->classification == JCType::TYPE_CLASSIFICATION::UNION)
						{
							llvm::Value *get_element = state.builder.CreateGEP(base_ptr, { llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0),  llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 0) });
							llvm::Value *get_union_element = state.builder.CreateBitCast(get_element, state.typeRegistry.GetType(type->MEMBER_TYPENAMES[i] + "*"));
						}
					}
				}
			}
        }
    }
    return nullptr;
}

const std::string *ASTMemberOperator::GetType(IREmitter::EmitterState &state)
{
	ASTIdentifier *inode = nullptr;
	if (id->GetNodeType() == IDENTIFIER)
		 inode = (ASTIdentifier*)id.get();

	if (!inode)
		return nullptr;

	//get the struct's symbol and type
    const Symbol *struct_symbol = id->GetSymbol(state);

	if (!struct_symbol)
		struct_symbol = id->GetSymbol(state);

	//if (!struct_symbol)
	//	return nullptr;

	const JCType *struct_type = nullptr;
	

	if (!struct_symbol)
		struct_type = base_struct_typeinfo;
	else
		struct_type = state.typeRegistry.GetTypeInfo(struct_symbol->type);


	ASTIdentifier *mid = nullptr;
	ASTMemberOperator *mmop = nullptr;

	if (member->GetNodeType() == IDENTIFIER)
		mid = (ASTIdentifier*)member.get();
	
	if (member->GetNodeType() == MEMBER_OP)
		mmop = (ASTMemberOperator*)member.get();


	//get the type of the member if possible, otherwise return nullptr
    for (unsigned int i = 0; i < struct_type->MEMBER_NAMES.size(); i++)
    {
		if (mid)
		{
			if (struct_type->MEMBER_NAMES[i] == mid->identifier)
				return state.typeRegistry.GetLifetimeTypeString(struct_type->MEMBER_TYPENAMES[i]);
		}
		if (mmop)
		{
			if (mmop->id->GetNodeType() == IDENTIFIER)
			{
				ASTIdentifier *ide = (ASTIdentifier*)mmop->id.get();
				if (struct_type->MEMBER_NAMES[i] == ide->identifier)
				{
					mmop->base_struct_typeinfo = state.typeRegistry.GetTypeInfo(struct_type->MEMBER_TYPENAMES[i]);
					return mmop->GetType(state);
				}
			}
			
		}
    }
    return nullptr;
}

const Symbol * ASTMemberOperator::GetSymbol(IREmitter::EmitterState & state)
{
	ASTIdentifier *inode = (ASTIdentifier*)id.get();

	//get the struct's symbol and type
	const Symbol *struct_symbol = id->GetSymbol(state);

	if (!struct_symbol)
		struct_symbol = id->GetSymbol(state);

	if (!struct_symbol)
		return nullptr;
	return struct_symbol;
}

const bool ASTMemberOperator::SyntheticEval(IREmitter::EmitterState & state)
{
	return true;
}
