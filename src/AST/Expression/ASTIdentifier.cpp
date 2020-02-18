#include <include/AST/Expression/ASTIdentifier.hpp>

ASTIdentifier::ASTIdentifier(const std::string &identifier) : identifier(identifier) {}

ASTIdentifier::ASTIdentifier() {}

const std::string *ASTIdentifier::GetType(IREmitter::EmitterState &state)
{
    Symbol *symbol = state.frontmost->GetSymbolByIdentifier(identifier);
    if (symbol)
        return &symbol->type;
    return state.typeRegistry.GetLifetimeTypeString(identifier);
}

const Symbol *ASTIdentifier::GetSymbol(IREmitter::EmitterState &state)
{
    return state.frontmost->GetSymbolByIdentifier(identifier);
}

llvm::Value *ASTIdentifier::EmitIR(IREmitter::EmitterState &state)
{
    const Symbol * s = state.frontmost->GetSymbolByIdentifier(identifier);
    if (s)
        return s->alloc_inst;
    return NULL;
}