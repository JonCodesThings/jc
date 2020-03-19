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
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.identifier = id->identifier;

    llvm::Type *t = state.typeRegistry.GetType(type->identifier);

    if (!t)
    {
        t = state.typeRegistry.UnwindPointerType(type->identifier);
        state.typeRegistry.AddType(type->identifier, *t, JCType::TYPE_CLASSIFICATION::POINTER);
    }

    auto temp = static_cast<ASTConstantInt*>(array_size.get());

    if (array_size)
        t = state.typeRegistry.GetArrayType(type->identifier, temp->constant);

    symbol.type = type->identifier;

	if (state.builder.GetInsertBlock()->getParent() == NULL)
	{
		//symbol.alloc_inst = new llvm::GlobalVariable(t, false, llvm::GlobalValue::ExternalLinkage, nullptr, symbol.identifier);
		state.module->getOrInsertGlobal(id->identifier, t);
		symbol.alloc_inst = state.module->getNamedGlobal(id->identifier);
		state.module->getNamedGlobal(id->identifier)->setLinkage(llvm::GlobalValue::ExternalLinkage);
		state.module->getNamedGlobal(id->identifier)->setInitializer(llvm::UndefValue::get(t));
	}
	else
		symbol.alloc_inst = state.builder.CreateAlloca(t, NULL, id->identifier);

    state.symbolStack.AddSymbol(symbol);

    if (node)
    {
        auto assignment = ASTVariableAssignment(*id, *node);
        id.release();
        node.release();
        assignment.EmitIR(state);
    }


    return symbol.alloc_inst;
}