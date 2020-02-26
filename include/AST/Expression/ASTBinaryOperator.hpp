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
        MULTIPLY,
        DIVIDE,
        EQUALITY,
        INEQUALITY,
        LESSER,
        GREATER,
        LESSER_OR_EQUAL,
        GREATER_OR_EQUAL
    } op;

    ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    const std::string *GetType(IREmitter::EmitterState &state);
};

#endif