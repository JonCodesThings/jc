#ifndef JC_ASTRETURNSTATEMENT_H
#define JC_ASTRETURNSTATEMENT_H

#include <include/AST/ASTStatement.hpp>

/*!
* \brief AST Return Statement Node
* AST Node representing return statements
*/
class ASTReturnStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTStatement> expr;

    ASTReturnStatement(ASTStatement &expr);

	const std::string *GetType(IREmitter::EmitterState &state);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const bool SyntheticEval(IREmitter::EmitterState &state);
};

#endif