#include <include/AST/Statement/ASTIfStatement.hpp>

ASTConditionalBlock::ASTConditionalBlock(ASTStatement &cond_expr, ASTBlock &then) : cond_expr(&cond_expr), then(&then) {}

ASTIfStatement::ASTIfStatement(std::vector<std::unique_ptr<ASTConditionalBlock>> &conditional_blocks, ASTBlock *otherwise) : 
    conditional_blocks(&conditional_blocks), otherwise(otherwise), ASTStatement(IF_STATEMENT) {}

llvm::Value *ASTIfStatement::EmitIR(IREmitter::EmitterState &state)
{
	//store the current insert point
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

	//create the final merge block
    llvm::BasicBlock *final_merge = llvm::BasicBlock::Create(state.context, "final_merge", current_function);

	//set the insert point of the final merge
    state.builder.SetInsertPoint(final_merge);

	//create the phi node in that final merge block
    llvm::PHINode *phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 0);

	//set the otherwise basic block to NULL for now
    llvm::BasicBlock *ot = NULL;

	//set the insert point to final merge again
    state.builder.SetInsertPoint(final_merge);

	//if there is an otherwise (or "else")
    if (otherwise)
    {
		//emit that block's IR
        llvm::Value *block = otherwise->EmitIR(state);

		//downcast
        ot = (llvm::BasicBlock *)block;

		//if that block doesn't contain a return add a branch to the final merge branch
        if (!otherwise->ContainsReturnStatement())
            state.builder.CreateBr(final_merge);
    }

	//reset the insert point
    state.builder.SetInsertPoint(current_insert);

	//iterate through all of the conditional blocks
    for (auto it = conditional_blocks->begin(); it != conditional_blocks->end(); it++)
    {
		//stor ethe current insert block
        current_insert = state.builder.GetInsertBlock();

		//get the condition associated with this conditional block by emitting IR
        llvm::Value *cond = (*it)->cond_expr->EmitIR(state);

		//get the block associated with this conditional block by emitting IR
        llvm::Value *block = (*it)->then->EmitIR(state);
		
		//downcast that block to an actual BasicBlock
		llvm::BasicBlock *br = (llvm::BasicBlock *)block;

		//create a new merge block
        llvm::BasicBlock *merge = llvm::BasicBlock::Create(state.context, "merge", current_function);

		//add to the new merge block a branch if the current conditional block has no return statement
        if (!(*it)->then->ContainsReturnStatement())
            state.builder.CreateBr(final_merge);

		//set the current insert point back to what it was at the start of this iteration
        state.builder.SetInsertPoint(current_insert);

		//create a conditional branch using the condition, branch block and merge
        state.builder.CreateCondBr(cond, br, merge);

		//set the inser point to the merge
        state.builder.SetInsertPoint(merge);

		//if the next block is the final conditional block
        if (std::next(it) == conditional_blocks->end())
        {
			//if there is no "else" block
            if (!ot)
            {
				//add incoming to the phi node and add a branch
                phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), merge);
                state.builder.CreateBr(final_merge);
            }
			//otherwise create a branch to the "else" block
            else
            {
                state.builder.CreateBr(ot);
            }
            

        }


        //state.builder.SetInsertPoint(merge);
    }

	//set the insert point to the final merge
    state.builder.SetInsertPoint(final_merge);

	//if there are no things to merge with the pi node remove it from the final merge
    if (phi->incoming_values().begin() == phi->incoming_values().end())
        phi->removeFromParent();

	//return the current insert block
    return current_insert;
}