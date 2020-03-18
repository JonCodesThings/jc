#include <include/IREmitter.hpp>
#include <include/AST.hpp>

bool IREmitter::EmitIR(ASTBlock *root)
{
    state.typeRegistry.SetupBuiltinJCTypes();

    if (!root)
        return false;

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
