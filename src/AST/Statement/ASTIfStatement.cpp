#include <include/AST/Statement/ASTIfStatement.hpp>

ASTConditionalBlock::ASTConditionalBlock(ASTStatement &cond_expr, ASTBlock &then) : cond_expr(&cond_expr), then(&then) {}

ASTIfStatement::ASTIfStatement(std::vector<std::unique_ptr<ASTConditionalBlock>> &conditional_blocks, ASTBlock *otherwise) : 
    conditional_blocks(&conditional_blocks), otherwise(otherwise), ASTStatement(IF_STATEMENT) {}

llvm::Value *ASTIfStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

    llvm::BasicBlock *final_merge = llvm::BasicBlock::Create(state.context, "final_merge", current_function);

    state.builder.SetInsertPoint(final_merge);

    llvm::PHINode *phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 0);

    llvm::BasicBlock *ot = NULL;

    state.builder.SetInsertPoint(final_merge);

    if (otherwise)
    {
        llvm::Value *block = otherwise->EmitIR(state);

        ot = (llvm::BasicBlock *)block;

        if (!otherwise->ContainsReturnStatement())
            state.builder.CreateBr(final_merge);
    }

    state.builder.SetInsertPoint(current_insert);

    for (auto it = conditional_blocks->begin(); it != conditional_blocks->end(); it++)
    {
        current_insert = state.builder.GetInsertBlock();

        llvm::Value *cond = (*it)->cond_expr->EmitIR(state);

        llvm::Value *block = (*it)->then->EmitIR(state);

        llvm::BasicBlock *br = (llvm::BasicBlock *)block;

        llvm::BasicBlock *merge = llvm::BasicBlock::Create(state.context, "merge", current_function);

        if (!(*it)->then->ContainsReturnStatement())
            state.builder.CreateBr(final_merge);

        state.builder.SetInsertPoint(current_insert);

        state.builder.CreateCondBr(cond, br, merge);

        state.builder.SetInsertPoint(merge);

        if (std::next(it) == conditional_blocks->end())
        {
            if (!ot)
            {
                phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), merge);
                state.builder.CreateBr(final_merge);
            }
            else
            {
                state.builder.CreateBr(ot);
            }
            

        }


        //state.builder.SetInsertPoint(merge);
    }

    state.builder.SetInsertPoint(final_merge);

    if (phi->incoming_values().begin() == phi->incoming_values().end())
        phi->removeFromParent();

    return current_insert;
}