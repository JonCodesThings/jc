#ifndef JC_ASTIFSTATEMENT_H
#define JC_ASTIFSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

/*!
* \brief Conditional Block
* Struct for a branch that will only run under a given condition expression
*/
struct ASTConditionalBlock
{
    ASTConditionalBlock(ASTStatement &cond_expr, ASTBlock &then);
    std::unique_ptr<ASTStatement> cond_expr;
    std::unique_ptr<ASTBlock> then;
};

/*!
* \brief AST If Statement Node
* AST Node representing an if-else branching chain. May be extended to support switch-case statements.
*/
class ASTIfStatement : public ASTStatement
{
public:
    std::unique_ptr<std::vector<std::unique_ptr<ASTConditionalBlock>>> conditional_blocks;
    std::unique_ptr<ASTBlock> otherwise;

    ASTIfStatement(std::vector<std::unique_ptr<ASTConditionalBlock>> &conditional_blocks, ASTBlock *otherwise);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif