#include <include/Module.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

extern std::unique_ptr<ASTBlock> base;
extern FILE *yyin;
extern const char *yycurrentfilename;
extern int yyparse();
extern TypeRegistry *registry;

Module::Module(const std::string &module_namespace, ASTBlock &block, const std::vector<std::string> &depends)
	: module_namespace(module_namespace), module_symbol_table(module_symbol_table), module_block(&block), module_depends(depends) {}

Module::~Module() {}

bool Module::IREmitted()
{
	return ir_flag;
}

const Symbol *Module::GetSymbol(const std::string &id)
{
	return module_symbol_table.GetSymbolByIdentifier(id);
}

void Module::AddDependencySymbols(const std::vector<Symbol> exported)
{
	module_dependency_symbols.insert(module_dependency_symbols.end(), exported.begin(), exported.end());
}

const std::vector<std::string>& Module::GetModuleDependencies() const
{
	return module_depends;
}

const std::string &Module::GetModuleNamespace() const
{
	return module_namespace;
}

const SymbolTable & Module::GetModuleSymbolTable() const
{
	return module_symbol_table;
}

bool Module::EmitIR(llvm::LLVMContext &context, TypeRegistry &registry)
{	
	//create a new llvm module
	llvm_mod = std::make_unique<llvm::Module>(module_namespace, context);

	//set up a new IR emitter instance
	IREmitter emit(*llvm_mod.get(), context, registry);
	printf("Emitting IR for module %s...\n", module_namespace.c_str());

	//get the emitter state
	IREmitter::EmitterState &se = emit.GetEmitterState();
	
	//inject the symbols for the imported modules into the current module's global symbol table
	for (auto &e : module_dependency_symbols)
	{
		if (e.classification == e.FUNCTION)
		{
			auto Func = llvm::Function::Create(e.function->getFunctionType(), llvm::GlobalValue::ExternalLinkage, e.identifier, llvm_mod.get());

			Symbol s;
			s.identifier = e.identifier;
			s.type = e.type;
			s.classification = Symbol::Classification::FUNCTION;
			s.function = Func;
			s.exported = false;

			se.symbolStack.AddSymbol(s);
		}
		else if (e.classification == e.VARIABLE)
		{
			llvm_mod->getOrInsertGlobal(e.identifier, se.typeRegistry.GetType(e.type));

			Symbol s;
			s.identifier = e.identifier;
			s.type = e.type;
			s.classification = Symbol::Classification::VARIABLE;
			s.exported = false;
			s.alloc_inst = llvm_mod->getNamedGlobal(e.identifier);
			llvm_mod->getNamedGlobal(e.identifier)->setLinkage(llvm::GlobalValue::ExternalLinkage);

			se.symbolStack.AddSymbol(s);
		}
	}

	//set the ir flag and copy the global symbol table for the module
	ir_flag = emit.EmitIR(module_block.get(), module_namespace, module_depends);
	module_symbol_table = emit.GetEmitterState().symbolStack.Top();

	if (!ir_flag)
		return ir_flag;

	//write the IR out to a file
	std::error_code ec;
	std::string o = module_namespace;
	o.append(".ir");
	llvm::raw_fd_ostream out(o, ec);
	llvm::WriteBitcodeToFile(*llvm_mod.get(), out);
	out.close();

	return ir_flag;
}
