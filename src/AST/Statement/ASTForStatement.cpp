#include <include/AST/Statement/ASTForStatement.hpp>

ASTForStatement::ASTForStatement(ASTStatement &first, ASTStatement &second, ASTStatement &third, ASTBlock &loop) :
    first(&first), second(&second), third(&third), loop(&loop), ASTStatement(FOR_STATEMENT) {}

llvm::Value *ASTForStatement::EmitIR(IREmitter::EmitterState &state)
{
	//get the current insert block
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

	//create a post loop block
    llvm::BasicBlock *pl = llvm::BasicBlock::Create(state.context, "post_loop", current_function);

	//set the current insert point to the insert point prior to making the post loop block
    state.builder.SetInsertPoint(current_insert);

	//emit the IR for the first statement of the for conditions
    llvm::Value *var = first->EmitIR(state);

	if (!var)
		return nullptr;

	//emit the IR for the loop internals
    llvm::Value *loop_internals = loop->EmitIR(state);

    if (!loop_internals)
        return nullptr;

	//cast the loop internals to a basic block
    llvm::BasicBlock *lvb = (llvm::BasicBlock *)loop_internals;

	//emit IR for the loop condition and iterate condition
    llvm::Value *loop_condition = second->EmitIR(state);

	if (!loop_condition)
		return nullptr;

    llvm::Value *iterate = third->EmitIR(state);

	if (!iterate)
		return nullptr;

	//make a branch for the loop condition
    state.builder.CreateCondBr(loop_condition, lvb, pl);

	//set the current insert back to what it was at the start of this function again
	//create another branch using the loop condition
    state.builder.SetInsertPoint(current_insert);
    llvm::Value *cond = second->EmitIR(state);
    state.builder.CreateCondBr(cond, lvb, pl);

	//set the insert point to the post loop block
    state.builder.SetInsertPoint(pl);

	//generate the required phi nodes
    llvm::PHINode *phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 2);
    phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), current_insert);
    phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 1), lvb);

	//return the post loop block
    return pl;
}