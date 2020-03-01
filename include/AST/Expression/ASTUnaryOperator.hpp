#ifndef JC_ASTUNARYOPERATOR_H
#define JC_ASTUNARYOPERATOR_H

#include <include/AST/ASTExpression.hpp>
#include <include/AST/Constant/ASTConstantInt.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>

class ASTUnaryOperator : public ASTExpression
{
public:
    std::unique_ptr<ASTNode> operatee;
    std::unique_ptr<ASTIdentifier> cast;
    std::unique_ptr<ASTConstantInt> index;

    enum OP
    {
        CAST,
        INCREMENT,
        DECREMENT,
        ADDRESS_OF,
        DEREFERENCE,
        ARRAY_INDEX
    } op;

    ASTUnaryOperator(ASTNode &operatee, OP op);

    ASTUnaryOperator(ASTNode &operatee, ASTIdentifier *identifier, OP op);
    
    ASTUnaryOperator(ASTNode &operatee, ASTConstantInt &index, OP op);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif