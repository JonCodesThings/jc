#ifndef JC_SYMBOLTABLE_H
#define JC_SYMBOLTABLE_H

#include <llvm/IR/Instructions.h>

#include <string>
#include <vector>

struct Symbol
{
    enum Classification
    {
        VARIABLE,
        FUNCTION
    } classification;

    std::string identifier;
    std::string type;
    llvm::AllocaInst *alloc_inst;
    
};

class SymbolTable
{
public:
    bool AddSymbol(const Symbol &symbol);
    Symbol *GetSymbolByIdentifier(const std::string &identifier);
private:
    std::vector<Symbol> symbols;
};

#endif