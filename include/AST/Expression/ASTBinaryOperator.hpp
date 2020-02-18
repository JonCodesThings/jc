#ifndef JC_ASTBINARYOPERATOR_H
#define JC_ASTBINARYOPERATOR_H

#include <include/AST/ASTExpression.hpp>

class ASTBinaryOperator : public ASTExpression
{
public:
    ASTNode &left;
    ASTNode &right;

    enum OP
    {
        ADD,
        SUBTRACT,
        MULTIPLE,
        DIVIDE
    } op;

    ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    const std::string *GetType(IREmitter::EmitterState &state);
};

#endif