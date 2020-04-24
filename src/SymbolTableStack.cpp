#include <include/SymbolTableStack.hpp>


SymbolTableStack::SymbolTableStack() { stack.push_back(SymbolTable("module")); }
SymbolTableStack::~SymbolTableStack() {}

bool SymbolTableStack::AddSymbol(const Symbol &symbol) 
{
    return stack.back().AddSymbol(symbol);
}

void SymbolTableStack::Clear()
{
	stack.clear();
}

Symbol *SymbolTableStack::GetSymbolByIdentifier(const std::string &identifier)
{
    Symbol *symbol = nullptr;
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        symbol = it->GetSymbolByIdentifier(identifier);
        if (symbol)
            break;
    }
    return symbol;
}

bool SymbolTableStack::Empty()
{
	return stack.empty();
}

void SymbolTableStack::Push(const std::string &id) 
{
    stack.push_back(SymbolTable(id));
}

void SymbolTableStack::Pop()
{
    stack.pop_back();
}

const unsigned int SymbolTableStack::Size()
{
	return stack.size();
}

SymbolTable & SymbolTableStack::Top()
{
	return stack.back();
}
