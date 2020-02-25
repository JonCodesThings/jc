#include <include/AST/Statement/ASTIfStatement.hpp>

ASTConditionalBlock::ASTConditionalBlock(ASTStatement &cond_expr, ASTBlock &then) : cond_expr(cond_expr), then(then) {}

ASTIfStatement::ASTIfStatement(std::vector<ASTConditionalBlock*> &conditional_blocks, ASTBlock *otherwise) : 
    conditional_blocks(conditional_blocks), otherwise(otherwise), ASTStatement(IF_STATEMENT) {}

llvm::Value *ASTIfStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

    llvm::BasicBlock *final_merge = llvm::BasicBlock::Create(state.context, "final_merge", current_function);

    state.builder.SetInsertPoint(final_merge);

    llvm::PHINode *phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 0);

    state.builder.SetInsertPoint(current_insert);

    for (auto &conditional_block : conditional_blocks)
    {
        llvm::Value *cond = conditional_block->cond_expr.EmitIR(state);

        llvm::Value *block = conditional_block->then.EmitIR(state);

        llvm::BasicBlock *br = (llvm::BasicBlock *)block;

        llvm::BasicBlock *merge = llvm::BasicBlock::Create(state.context, "merge", current_function);

        state.builder.SetInsertPoint(current_insert);

        state.builder.CreateCondBr(cond, br, merge);

        state.builder.SetInsertPoint(merge);

        state.builder.CreateBr(final_merge);

        phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), merge);
    }

    if (otherwise)
    {
        llvm::Value *block = otherwise->EmitIR(state);

        llvm::BasicBlock *ot = (llvm::BasicBlock *)block;

        //state.builder.CreateBr(final_merge);
    }

    state.builder.SetInsertPoint(final_merge);

    return current_insert;
}