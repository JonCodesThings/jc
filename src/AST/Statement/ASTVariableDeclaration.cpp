#include <include/AST/Statement/ASTVariableDeclaration.hpp>

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id) : 
    type(type), id(id), node(NULL), array_size(NULL), ASTStatement(VARIABLE_DECLARATION) {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node) : 
    type(type), id(id), node(&node), array_size(NULL), ASTStatement(VARIABLE_DECLARATION)  {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size) : 
    type(type), id(id), node(NULL), array_size(&array_size), ASTStatement(VARIABLE_DECLARATION)  {}

llvm::Value * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.identifier = id.identifier;

    llvm::Type *t = state.typeRegistry.GetType(type.identifier);

    if (!t)
        t = state.typeRegistry.UnwindPointerType(type.identifier);

    auto temp = (ASTConstantInt*)array_size;

    if (array_size)
        t = state.typeRegistry.GetArrayType(type.identifier, temp->constant);
    else
    {
        symbol.type = type.identifier;
    }

    symbol.alloc_inst = state.builder.CreateAlloca(t, NULL, id.identifier);

    if (node)
    {
        llvm::Value *v = node->EmitIR(state);
        state.builder.CreateStore(v, symbol.alloc_inst);
    }

    state.frontmost->AddSymbol(symbol);

    return symbol.alloc_inst;
}