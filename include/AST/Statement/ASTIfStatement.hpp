#ifndef JC_ASTIFSTATEMENT_H
#define JC_ASTIFSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

class ASTIfStatement : public ASTStatement
{
public:
    ASTStatement &cond_expr;
    ASTBlock &then;
    ASTBlock *otherwise;
    std::vector<ASTIfStatement*> elif;

    ASTIfStatement(ASTStatement &cond_expr, ASTBlock &then, ASTBlock *otherwise);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif