#ifndef JC_ASTFORSTATEMENT_H
#define JC_ASTFORSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

/*!
* \brief AST Constant Node
* AST Node representing a for loop construct
*/
class ASTForStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTStatement> first;
    std::unique_ptr<ASTStatement> second;
    std::unique_ptr<ASTStatement> third;
    std::unique_ptr<ASTStatement> loop;

    ASTForStatement(ASTStatement &first, ASTStatement &second, ASTStatement &third, ASTBlock &loop);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif