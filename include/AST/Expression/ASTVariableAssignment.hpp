#ifndef JC_ASTVARIABLEASSIGMENT_H
#define JC_ASTVARIABLEASSIGMENT_H

#include <include/AST/ASTExpression.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>


class ASTVariableAssignment : public ASTExpression
{
public:
    std::unique_ptr<ASTNode> assign_to;
    std::unique_ptr<ASTNode> val;

    ASTVariableAssignment(ASTNode &assign_to, ASTNode &val);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif