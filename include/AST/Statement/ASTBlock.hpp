#ifndef JC_ASTBLOCK_H
#define JC_ASTBLOCK_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

/*!
* \brief AST Block Node
*/
class ASTBlock : public ASTStatement
{
public:
    std::unique_ptr<std::vector<std::unique_ptr<ASTStatement>>> block; //\brief std::vector of statements that the block is composed of

    llvm::BasicBlock *b; //\brief LLVM Basic Block representation

    bool returned = false; //\brief Flag to check if the block contains a return statement

    ASTBlock();

    ASTBlock(std::vector<std::unique_ptr<ASTStatement>> &block);

    bool ContainsReturnStatement();

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args);

private:
    llvm::Value *CreateBasicBlock(IREmitter::EmitterState &state, const std::string &name);
};

#endif