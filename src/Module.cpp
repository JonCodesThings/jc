#include <include/Module.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

extern std::unique_ptr<ASTBlock> base;
extern FILE *yyin;
extern const char *yycurrentfilename;
extern int yyparse();
extern TypeRegistry *registry;

Module::Module(const std::string &module_namespace, SymbolTable &module_symbol_table, ASTBlock &block) : module_namespace(module_namespace), module_symbol_table(module_symbol_table), module_block(&block) {}

Module::~Module() {}

bool Module::IREmitted()
{
	return ir_flag;
}

const Symbol *Module::GetSymbol(const std::string &id)
{
	return module_symbol_table.GetSymbolByIdentifier(id);
}

const std::vector<std::string>& Module::GetModuleDependencies()
{
	return module_depends;
}

const std::string &Module::GetModuleNamespace()
{
	return module_namespace;
}

bool Module::EmitIR(llvm::LLVMContext &context, TypeRegistry &registry)
{
	std::unique_ptr<llvm::Module> m = std::make_unique<llvm::Module>(module_namespace, context);
	IREmitter emit(*m.get(), context, registry);
	ir_flag = emit.EmitIR(module_block.get());

	if (!ir_flag)
		return ir_flag;

	std::error_code ec;
	std::string o = module_namespace;
	o.append(".ir");
	llvm::raw_fd_ostream out(o, ec);
	llvm::WriteBitcodeToFile(*m.get(), out);
	out.close();

	return ir_flag;
}
