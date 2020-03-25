#ifndef JC_ASTIDENTIFIER_H
#define JC_ASTIDENTIFIER_H

#include <include/AST/ASTExpression.hpp>

/*!
* \brief AST Identifier Node
* AST Node that represent identifiers
*/
class ASTIdentifier : public ASTExpression
{
public:
    std::string identifier;

    ASTIdentifier(const std::string &identifier);

    ASTIdentifier();

    const std::string *GetType(IREmitter::EmitterState &state);

    const Symbol *GetSymbol(IREmitter::EmitterState &state);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif