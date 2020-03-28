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

	if (!type)
	{
		const std::string *s = node->GetType(state);
		typestring = *s;
	}
	else
		typestring = type->identifier;

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
        assignment.EmitIR(state);
    }
	else if (init_list)
	{
		printf("%d\n", init_list->size());
		int index = 0;
		for (auto &node : *init_list.get())
		{
			ASTVariableAssignment assign(*new ASTUnaryOperator(*new ASTIdentifier(symbol.identifier), *new ASTConstantInt(index), ASTUnaryOperator::ARRAY_INDEX), *node.release());
			assign.EmitIR(state);
			index++;
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
		typestring = type->identifier;

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