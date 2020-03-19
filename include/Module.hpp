#ifndef JC_MODULE_H
#define JC_MODULE_H

#include "SymbolTable.hpp"

#include <include/AST/Statement/ASTBlock.hpp>

class Module
{
public:
	Module(const std::string &module_namespace, ASTBlock &base, const std::vector<std::string> &depends);
	~Module();

	bool EmitIR(llvm::LLVMContext &context, TypeRegistry &registry);
	bool IREmitted();
	llvm::Module *GetLLVMModule() { return llvm_mod.get(); };
	const Symbol *GetSymbol(const std::string &id);
	void AddDependencySymbols(const std::vector<Symbol> exported);
	const std::vector<std::string> &GetModuleDependencies() const;
	const std::string &GetModuleNamespace() const;
	const SymbolTable &GetModuleSymbolTable() const;
private:
	std::string module_namespace;
	SymbolTable module_symbol_table;
	std::vector<std::string> module_depends;
	std::vector<Symbol> module_dependency_symbols;
	std::unique_ptr<ASTBlock> module_block;
	std::unique_ptr<llvm::Module> llvm_mod;
	bool ir_flag = false;
};

#endif