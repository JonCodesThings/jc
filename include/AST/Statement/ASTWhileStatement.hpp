#ifndef JC_ASTWHILESTATEMENT_H
#define JC_ASTWHILESTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

/*!
* \brief AST While Statement Node
* AST Node representing a while loop construct
*/
class ASTWhileStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTStatement> cond_expr;
    std::unique_ptr<ASTBlock> loop;

    ASTWhileStatement(ASTStatement &cond_expr, ASTBlock &loop);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif