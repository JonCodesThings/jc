#include <include/AST/Statement/ASTVariableDeclaration.hpp>

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id) : 
    type(type), id(id), node(NULL), array_size(NULL) {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTNode &node) : 
    type(type), id(id), node(&node), array_size(NULL) {}

ASTVariableDeclaration::ASTVariableDeclaration(ASTIdentifier &type, ASTIdentifier &id, ASTConstant &array_size) : 
    type(type), id(id), node(NULL), array_size(&array_size) {}

llvm::Value * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.identifier = id.identifier;

    auto temp = (ASTConstantInt*)array_size;

    if (array_size)
    {
        symbol.alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetArrayType(type.identifier, temp->constant), NULL, id.identifier);
    }
    else
    {
        symbol.alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(type.identifier), NULL, id.identifier);
        symbol.type = type.identifier;
    }

    if (node)
    {
        llvm::Value *v = node->EmitIR(state);
        state.builder.CreateStore(v, symbol.alloc_inst);
    }

    state.frontmost->AddSymbol(symbol);

    return symbol.alloc_inst;
}