#ifndef JC_ASTBINARYOPERATOR_H
#define JC_ASTBINARYOPERATOR_H

#include <include/AST/ASTExpression.hpp>

/*!
* \brief AST Binary Operator Node
*/
class ASTBinaryOperator : public ASTExpression
{
public:
    std::unique_ptr<ASTNode> left; // \brief Left side of operator node
    std::unique_ptr<ASTNode> right; // \brief Right side of operator node

	// \brief Operator type enum
    enum OP
    {
        ADD = 0,
        SUBTRACT = 1,
        MULTIPLY = 2,
        DIVIDE = 3,
        EQUALITY = 4,
        INEQUALITY = 5,
        LESSER = 6,
        GREATER = 7,
        LESSER_OR_EQUAL = 8,
        GREATER_OR_EQUAL = 9,
		BITWISE_AND = 10,
		BITWISE_OR = 11,
		BITWISE_LEFT_SHIFT = 12,
		BITWISE_RIGHT_SHIFT = 13,
		MODULO = 14
    } op;

    ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    const std::string *GetType(IREmitter::EmitterState &state);
	const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif