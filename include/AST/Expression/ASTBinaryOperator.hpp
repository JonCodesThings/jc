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
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        EQUALITY,
        INEQUALITY,
        LESSER,
        GREATER,
        LESSER_OR_EQUAL,
        GREATER_OR_EQUAL,
		BITWISE_AND,
		BITWISE_OR,
		BITWISE_LEFT_SHIFT,
		BITWISE_RIGHT_SHIFT,
		MODULO
    } op;

    ASTBinaryOperator(ASTNode &left, ASTNode &right, OP op);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    const std::string *GetType(IREmitter::EmitterState &state);
	const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif