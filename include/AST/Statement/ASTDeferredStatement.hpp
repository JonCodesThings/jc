#ifndef JC_ASTDEFERSTATEMENT_H
#define JC_ASTDEFERSTATEMENT_H

#include <include/AST/ASTStatement.hpp>

/*!
* \brief AST Deferred Statement Node
* Class for AST Nodes that defer an action to current scope exit
*/
class ASTDeferredStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTStatement> defer;

    ASTDeferredStatement(ASTStatement &defer);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif