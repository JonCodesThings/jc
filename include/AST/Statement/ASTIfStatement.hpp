#ifndef JC_ASTIFSTATEMENT_H
#define JC_ASTIFSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

class ASTIfStatement : public ASTStatement
{
public:
    ASTStatement &cond_expr;
    ASTBlock &then;

    //ASTIfStatement(ASTStatement &cond_expr);
    ASTIfStatement(ASTStatement &cond_expr, ASTBlock &then);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif