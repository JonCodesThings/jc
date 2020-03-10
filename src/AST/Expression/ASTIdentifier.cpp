#include <include/AST/Expression/ASTIdentifier.hpp>

ASTIdentifier::ASTIdentifier(const std::string &identifier) : identifier(identifier), ASTExpression(IDENTIFIER) {}

ASTIdentifier::ASTIdentifier() : ASTExpression(IDENTIFIER) {}

const std::string *ASTIdentifier::GetType(IREmitter::EmitterState &state)
{
    Symbol *symbol = state.symbolStack.GetSymbolByIdentifier(identifier);
    if (symbol)
        return state.typeRegistry.GetLifetimeTypeString(symbol->type);
    return state.typeRegistry.GetLifetimeTypeString(identifier);
}

const Symbol *ASTIdentifier::GetSymbol(IREmitter::EmitterState &state)
{
    return state.symbolStack.GetSymbolByIdentifier(identifier);
}

llvm::Value *ASTIdentifier::EmitIR(IREmitter::EmitterState &state)
{
    const Symbol * s = state.symbolStack.GetSymbolByIdentifier(identifier);
    if (s)
        return s->alloc_inst;
    return NULL;
}