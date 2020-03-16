#ifndef JC_MODULE_H
#define JC_MODULE_H

#include "SymbolTable.hpp"

#include <include/AST/Statement/ASTBlock.hpp>

class Module
{
public:
	Module(const std::string &module_namespace, SymbolTable &module_symbol_table, ASTBlock &base);
	~Module();

	bool EmitIR(llvm::LLVMContext &context, TypeRegistry &registry);
	bool IREmitted();
	const Symbol *GetSymbol(const std::string &id);
	const std::vector<std::string> &GetModuleDependencies();
	const std::string &GetModuleNamespace();
private:
	std::string module_namespace;
	SymbolTable &module_symbol_table;
	std::vector<std::string> module_depends;
	std::unique_ptr<ASTBlock> module_block;
	bool ir_flag = false;
};

#endif