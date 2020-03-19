#include <include/SymbolTableStack.hpp>


SymbolTableStack::SymbolTableStack() { stack.push_back(SymbolTable("module")); }
SymbolTableStack::~SymbolTableStack() {}

bool SymbolTableStack::AddSymbol(const Symbol &symbol) 
{
    return stack.back().AddSymbol(symbol);
}

Symbol *SymbolTableStack::GetSymbolByIdentifier(const std::string &identifier)
{
    Symbol *symbol = NULL;
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        symbol = it->GetSymbolByIdentifier(identifier);
        if (symbol)
            break;
    }
    //printf("Symbol %s at %p\n", identifier.c_str(), symbol);
    return symbol;
}

void SymbolTableStack::Push(const std::string &id) 
{
    stack.push_back(SymbolTable(id));
}

void SymbolTableStack::Pop()
{
    stack.pop_back();
}

SymbolTable & SymbolTableStack::Top()
{
	return stack.back();
}
