#ifndef JC_ASTWHILESTATEMENT_H
#define JC_ASTWHILESTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

class ASTWhileStatement : public ASTStatement
{
public:
    ASTStatement &cond_expr;
    ASTBlock &loop;

    ASTWhileStatement(ASTStatement &cond_expr, ASTBlock &loop);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif