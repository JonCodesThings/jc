#include <include/SymbolTable.hpp>

SymbolTable::SymbolTable() : id("GLOBAL_SCOPED"), parent(NULL), child(NULL) {}

SymbolTable::SymbolTable(const std::string &id, SymbolTable &table) : id(id), parent(&table), child(NULL) { /*printf("%s\n", id.c_str());*/ }

bool SymbolTable::AddSymbol(const Symbol &symbol)
{
    Symbol * existing = GetSymbolByIdentifier(symbol.identifier);

    if (!existing)
    {
        symbols.push_back(symbol);
        return true;
    }
    return false;
}

SymbolTable *SymbolTable::GetParentTable()
{
    return parent;
}

SymbolTable *SymbolTable::CreateChildTable(const std::string &id)
{
    child = new SymbolTable(id, *this);

    return child;
}

Symbol *SymbolTable::GetSymbolByIdentifier(const std::string &identifier)
{
    for (auto &symbol : symbols)
    {
        if (symbol.identifier == identifier)
            return &symbol;
    }
    return NULL;
}