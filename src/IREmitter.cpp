#include <include/IREmitter.hpp>
#include <include/AST.hpp>

bool IREmitter::EmitIR(ASTBlock *root)
{
    state.typeRegistry.SetupBuiltinJCTypes();

    if (!root)
        return false;

    for (auto statement : root->block)
    {
        statement->EmitIR(state);
    }

    state.module.print(llvm::errs(), nullptr);

    return true;
}