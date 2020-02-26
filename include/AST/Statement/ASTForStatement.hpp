#ifndef JC_ASTFORSTATEMENT_H
#define JC_ASTFORSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>

class ASTForStatement : public ASTStatement
{
public:
    ASTStatement &first;
    ASTStatement &second;
    ASTStatement &third;
    ASTBlock &loop;

    ASTForStatement(ASTStatement &first, ASTStatement &second, ASTStatement &third, ASTBlock &loop);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif