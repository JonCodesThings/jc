#ifndef JC_ASTDEFERSTATEMENT_H
#define JC_ASTDEFERSTATEMENT_H

#include <include/AST/ASTStatement.hpp>

class ASTDeferredStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTStatement> defer;

    ASTDeferredStatement(ASTStatement &defer);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif