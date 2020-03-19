#include <include/SymbolTable.hpp>


SymbolTable::SymbolTable(const std::string &id) : id(id) {}

SymbolTable::~SymbolTable() {}

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

Symbol *SymbolTable::GetSymbolByIdentifier(const std::string &identifier)
{
    for (auto &symbol : symbols)
    {
        if (symbol.identifier == identifier)
            return &symbol;
    }        
    return NULL;
}

std::vector<Symbol> SymbolTable::GetExportedSymbols() const
{
	std::vector<Symbol> exported;

	for (auto s : symbols)
	{
		if (s.exported)
			exported.push_back(s);
	}

	return exported;
}
