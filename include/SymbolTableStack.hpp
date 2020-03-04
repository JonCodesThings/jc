#ifndef JC_SYMBOLTABLESTACK_H
#define JC_SYMBOLTABLESTACK_H

#include <include/SymbolTable.hpp>

#include <stack>
#include <string>
#include <vector>

class SymbolTableStack
{
public:
    SymbolTableStack();
    ~SymbolTableStack();
    bool AddSymbol(const Symbol &symbol);
    Symbol *GetSymbolByIdentifier(const std::string &identifier);
    void Push(const std::string &id);
    void Pop();
private:
    std::vector<SymbolTable> stack;
};

#endif