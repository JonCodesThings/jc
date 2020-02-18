#ifndef JC_ASTVARIABLEASSIGMENT_H
#define JC_ASTVARIABLEASSIGMENT_H

#include <include/AST/ASTExpression.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>


class ASTVariableAssignment : public ASTExpression
{
public:
    ASTIdentifier *id;
    ASTNode &node;
    ASTNode *array_index;

    ASTVariableAssignment(ASTIdentifier &id, ASTNode &node);
    ASTVariableAssignment(ASTNode &array_index, ASTNode &node);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif