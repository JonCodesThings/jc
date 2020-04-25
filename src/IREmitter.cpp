#include <include/IREmitter.hpp>
#include <include/AST.hpp>

IREmitter::EmitterState &IREmitter::GetEmitterState()
{
	return state;
}

bool IREmitter::EmitIR(ASTBlock *root, const std::string &module_name, const std::vector<std::string> &module_imports)
{
	//set up the built in types
    state.typeRegistry.SetupBuiltinJCTypes();

	state.imported_modules = module_imports;
	state.module_name = module_name;

    if (!root)
        return false;

	//emit the IR for the entire AST
    for (auto &statement : *root->block)
    {
        auto result = statement->EmitIR(state);
        if (!result)
            return false;
    }

    //state.module->print(llvm::errs(), nullptr);

    return true;
}

void IREmitter::SetModule(llvm::Module & module)
{
	state.module = &module;
}
