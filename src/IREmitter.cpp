#include <include/IREmitter.hpp>

bool IREmitter::EmitIR(ASTBlock &root)
{
    for (auto statement : root.block)
    {
        statement->EmitIR(builder, context, module);
    }

    module.print(llvm::errs(), nullptr);

    return true;
}