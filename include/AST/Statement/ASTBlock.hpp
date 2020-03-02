#ifndef JC_ASTBLOCK_H
#define JC_ASTBLOCK_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

class ASTBlock : public ASTStatement
{
public:
    std::unique_ptr<std::vector<std::unique_ptr<ASTStatement>>> block;

    llvm::BasicBlock *b;

    bool returned = false;

    ASTBlock();

    ASTBlock(std::vector<std::unique_ptr<ASTStatement>> &block);

    bool ContainsReturnStatement();

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args);

private:
    llvm::Value *CreateBasicBlock(IREmitter::EmitterState &state, const std::string &name);
};

#endif