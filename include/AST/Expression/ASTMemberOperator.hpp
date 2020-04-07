#ifndef JC_ASTMEMBEROPERATOR_H
#define JC_ASTMEMBEROPERATOR_H

#include <include/AST/ASTExpression.hpp>

#include <include/AST/Expression/ASTIdentifier.hpp>

/*!
* \brief AST Member Operator Node
* AST Node that is used for member operators on a given identifier
*/
class ASTMemberOperator : public ASTExpression
{
public:
    std::unique_ptr<ASTIdentifier> id;
    std::unique_ptr<ASTIdentifier> member_id;

    enum OP
    {
        DOT,
        ARROW
    } op;

    ASTMemberOperator(ASTIdentifier &id, ASTIdentifier &member, OP op);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    const std::string *GetType(IREmitter::EmitterState &state);
	const Symbol *GetSymbol(IREmitter::EmitterState &state);
	const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif