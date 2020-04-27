#ifndef JC_ASTUNARYOPERATOR_H
#define JC_ASTUNARYOPERATOR_H

#include <include/AST/ASTExpression.hpp>
#include <include/AST/Constant/ASTConstantInt.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>

/*!
* \brief AST Unary Operator Node
* AST Node for unary operators
*/
class ASTUnaryOperator : public ASTExpression
{
public:
    std::unique_ptr<ASTNode> operatee;
    std::unique_ptr<ASTIdentifier> cast;
    std::unique_ptr<ASTConstantInt> index;

    enum OP
    {
        CAST = 0,
        INCREMENT = 1,
        DECREMENT = 2,
        ADDRESS_OF = 3,
        DEREFERENCE = 4,
        ARRAY_INDEX = 5,
		MINUS = 6,
		PLUS = 7
    } op;

    ASTUnaryOperator(ASTNode &operatee, OP op);

    ASTUnaryOperator(ASTNode &operatee, ASTIdentifier *identifier, OP op);
    
    ASTUnaryOperator(ASTNode &operatee, ASTConstantInt &index, OP op);

    const std::string *GetType(IREmitter::EmitterState &state);

	const Symbol *GetSymbol(IREmitter::EmitterState &state);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif