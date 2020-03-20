#include <include/AST/Statement/ASTVariableDeclaration.hpp>

#include <include/AST/Expression/ASTVariableAssignment.hpp>

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id) : 
    type(&type), id(&id), node(), array_size(), ASTStatement(VARIABLE_DECLARATION) {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node) : 
    type(&type), id(&id), node(&node), array_size(), ASTStatement(VARIABLE_DECLARATION)  {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size) : 
    type(&type), id(&id), node(), array_size(&array_size), ASTStatement(VARIABLE_DECLARATION)  {}

llvm::Value * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
	//create a symbol struct instance
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.identifier = id->identifier;

	//get the llvm type
    llvm::Type *t = state.typeRegistry.GetType(type->identifier);

	//otherwise unwind the pointer type and store it in the registry
    if (!t)
    {
        t = state.typeRegistry.UnwindPointerType(type->identifier);
        state.typeRegistry.AddType(type->identifier, *t, JCType::TYPE_CLASSIFICATION::POINTER);
    }

	//temp cast to an ASTConstantInt
    auto temp = static_cast<ASTConstantInt*>(array_size.get());

	//if it is valid get the array type instead
    if (array_size)
        t = state.typeRegistry.GetArrayType(type->identifier, temp->constant);

	//set the type string
    symbol.type = type->identifier;

	//if there is no parent function set up a global variable
	if (state.builder.GetInsertBlock()->getParent() == NULL)
	{
		//symbol.alloc_inst = new llvm::GlobalVariable(t, false, llvm::GlobalValue::ExternalLinkage, nullptr, symbol.identifier);
		state.module->getOrInsertGlobal(id->identifier, t);
		symbol.alloc_inst = state.module->getNamedGlobal(id->identifier);
		state.module->getNamedGlobal(id->identifier)->setLinkage(llvm::GlobalValue::ExternalLinkage);
		state.module->getNamedGlobal(id->identifier)->setInitializer(llvm::UndefValue::get(t));
	}
	//otherwise create an allocinst
	else
		symbol.alloc_inst = state.builder.CreateAlloca(t, NULL, id->identifier);

	//set the export flag to the appropriate value
	symbol.exported = exporting;

	//add the symbol to the stack
    state.symbolStack.AddSymbol(symbol);

	//if there is a node to assign the first value
    if (node)
    {
		//create an assignment operation and release ownership of certain objects while emitting IR
        auto assignment = ASTVariableAssignment(*id, *node);
        id.release();
        node.release();
        assignment.EmitIR(state);
    }
	
	//return the symbols allocinst
    return symbol.alloc_inst;
}