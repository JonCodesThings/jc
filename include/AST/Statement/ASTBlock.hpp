#ifndef JC_ASTBLOCK_H
#define JC_ASTBLOCK_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

class ASTBlock : public ASTStatement
{
public:
    std::vector<ASTStatement*> &block;

    llvm::BasicBlock *b;

    bool returned = false;

    ASTBlock();

    ASTBlock(std::vector<ASTStatement*> &block);

    bool ContainsReturnStatement();

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args, llvm::Function &func);
};

#endif