#include <include/AST/Statement/ASTVariableDeclaration.hpp>

#include <include/AST/Expression/ASTVariableAssignment.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

#include <include/AST/Expression/ASTMemberOperator.hpp>

#include <include/AST/Constant/ASTConstantNullptr.hpp>

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id) : 
    type(&type), id(&id), node(), array_size(), ASTStatement(VARIABLE_DECLARATION) {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node) : 
    type(&type), id(&id), node(&node), array_size(), ASTStatement(VARIABLE_DECLARATION)  {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size) : 
    type(&type), id(&id), node(), array_size(&array_size), ASTStatement(VARIABLE_DECLARATION)  {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size, std::vector<std::unique_ptr<ASTNode>> &init_list) :
	type(&type), id(&id), node(), array_size(&array_size), init_list(&init_list), ASTStatement(VARIABLE_DECLARATION) {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &id, ASTNode &node) : type(), id(&id), node(&node), array_size(), ASTStatement(VARIABLE_DECLARATION) {}

llvm::Value * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
	llvm::Type *t;
	std::string typestring;

	//create a symbol struct instance
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.identifier = id->identifier;

	bool inferred = false;

	if (!type)
	{
		const std::string *s = node->GetType(state);
		typestring = *s;
		inferred = true;
	}
	else
		typestring = StripTypename(type->identifier);

	std::string raw_type;
	type ? raw_type = type->identifier : raw_type = "";
	symbol.type = typestring;

	//get the llvm type
	t = state.typeRegistry.GetType(typestring, state.imported_modules, state.module_name);

	//otherwise unwind the pointer type and store it in the registry
	if (!t && typestring.find('*') != std::string::npos)
	{
		t = state.typeRegistry.UnwindPointerType(typestring);
		state.typeRegistry.AddType(typestring, *t, JCType::TYPE_CLASSIFICATION::POINTER);
	}

	//temp cast to an ASTConstantInt
	auto temp = static_cast<ASTConstantInt*>(array_size.get());

	if (temp)
		symbol.array_size = temp->constant;

	//if it is valid get the array type instead
	if (array_size)
		t = state.typeRegistry.GetArrayType(typestring, temp->constant);

	if (!t)
	{
		printf("Error in module %s: Type not found. Module containing type definition not imported or no imported module exports a type definition for type <%s>. \n", state.module_name.c_str(), typestring.c_str());
		return nullptr;
	}

	//set the type string
	symbol.full_type = raw_type;

	//if there is no parent function set up a global variable
	if (state.builder.GetInsertBlock()->getParent() == nullptr)
	{
		//symbol.alloc_inst = new llvm::GlobalVariable(t, false, llvm::GlobalValue::ExternalLinkage, nullptrptr, symbol.identifier);
		state.module->getOrInsertGlobal(id->identifier, t);
		symbol.alloc_inst = state.module->getNamedGlobal(id->identifier);
		state.module->getNamedGlobal(id->identifier)->setLinkage(llvm::GlobalValue::ExternalLinkage);
		state.module->getNamedGlobal(id->identifier)->setInitializer(llvm::UndefValue::get(t));
	}
	//otherwise create an allocinst
	else
		symbol.alloc_inst = state.builder.CreateAlloca(t, nullptr, id->identifier);

	//set the export flag to the appropriate value
	symbol.exported = exporting;

	if (!inferred)
	{
		symbol.mut = TypenameMutable(raw_type);
		symbol.ptr_mut = TypenamePtrMutable(raw_type);

		if (array_size)
			symbol.ptr_mut = mut;
	}
	else
	{
		symbol.mut = true;
		symbol.ptr_mut = true;
	}


	//add the symbol to the stack
    state.symbolStack.AddSymbol(symbol);

	const JCType *typeinfo = state.typeRegistry.GetTypeInfo(symbol.type);

	//if there is a node to assign the first value
    if (node)
    {
		//create an assignment operation and release ownership of certain objects while emitting IR
		if (node->GetNodeType() == NULLPTR)
		{
			ASTConstantNullptr *np = (ASTConstantNullptr*)node.get();
			np->nullptr_type = (llvm::PointerType*)state.typeRegistry.GetType(symbol.type);
			np->nullptrtype_str = state.typeRegistry.GetLifetimeTypeString(symbol.type);
		}
        auto assignment = ASTVariableAssignment(*id, *node);
        id.release();
        node.release();
        auto emit = assignment.EmitIR(state);
		if (!emit)
			return nullptr;
    }
	else if (init_list)
	{
		int index = 0;
		for (auto &node : *init_list.get())
		{
			ASTVariableAssignment assign(*new ASTUnaryOperator(*new ASTIdentifier(symbol.identifier), *new ASTConstantInt(index), ASTUnaryOperator::ARRAY_INDEX), *node.release());
			index++;
			auto emit = assign.EmitIR(state);
			if (!emit)
				return nullptr;
		}
	}
	else if (typeinfo->classification == JCType::TYPE_CLASSIFICATION::STRUCT)
	{
		for (int i = 0; i < typeinfo->MEMBER_NAMES.size(); i++)
		{
			if (typeinfo->MEMBER_DEFAULTS[i] != nullptr)
			{
				ASTMemberOperator member(*new ASTIdentifier(*id), *new ASTIdentifier(typeinfo->MEMBER_NAMES[i]), ASTMemberOperator::DOT);
				state.builder.CreateStore(typeinfo->MEMBER_DEFAULTS[i], member.EmitIR(state));
			}
		}
	}
	
	//return the symbols allocinst
    return symbol.alloc_inst;
}

const bool ASTVariableDeclaration::SyntheticEval(IREmitter::EmitterState &state)
{
	llvm::Type *t;
	std::string typestring;

	//create a symbol struct instance
	Symbol symbol;
	symbol.classification = Symbol::VARIABLE;
	symbol.identifier = id->identifier;

	if (!type)
	{
		const std::string *s = node->GetType(state);
		typestring = *s;
	}
	else
		typestring = StripTypename(type->identifier);

	//get the llvm type
	t = state.typeRegistry.GetType(typestring);

	//otherwise unwind the pointer type and store it in the registry
	if (!t)
	{
		t = state.typeRegistry.UnwindPointerType(typestring);
		state.typeRegistry.AddType(typestring, *t, JCType::TYPE_CLASSIFICATION::POINTER);
	}

	//temp cast to an ASTConstantInt
	auto temp = static_cast<ASTConstantInt*>(array_size.get());

	//if it is valid get the array type instead
	if (array_size)
		t = state.typeRegistry.GetArrayType(typestring, temp->constant);

	//set the type string
	symbol.type = typestring;

	//set the export flag to the appropriate value
	symbol.exported = exporting;

	//add the symbol to the stack
	state.syntheticStack.AddSymbol(symbol);

	return true;
}