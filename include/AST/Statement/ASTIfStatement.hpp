#ifndef JC_ASTIFSTATEMENT_H
#define JC_ASTIFSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

struct ASTConditionalBlock
{
    ASTConditionalBlock(ASTStatement &cond_expr, ASTBlock &then);
    ASTStatement &cond_expr;
    ASTBlock &then;
};

class ASTIfStatement : public ASTStatement
{
public:
    std::vector<ASTConditionalBlock*> &conditional_blocks;
    ASTBlock *otherwise;

    ASTIfStatement(std::vector<ASTConditionalBlock*> &conditional_blocks, ASTBlock *otherwise);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif