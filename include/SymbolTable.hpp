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
	llvm::Function *function;
    unsigned int array_size = 1;
	bool exported = false;
};

class SymbolTable
{
public:
    SymbolTable(const std::string &id);
    ~SymbolTable();
    bool AddSymbol(const Symbol &symbol);
    Symbol *GetSymbolByIdentifier(const std::string &identifier);
	std::vector<Symbol> GetExportedSymbols() const;
private:
    std::vector<Symbol> symbols;

    std::string id;
};

#endif