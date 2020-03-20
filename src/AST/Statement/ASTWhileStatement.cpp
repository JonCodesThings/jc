#include <include/AST/Statement/ASTWhileStatement.hpp>

ASTWhileStatement::ASTWhileStatement(ASTStatement &cond_expr, ASTBlock &loop) : cond_expr(&cond_expr), loop(&loop), ASTStatement(WHILE_STATEMENT) {}

llvm::Value *ASTWhileStatement::EmitIR(IREmitter::EmitterState &state)
{
	//store the current insert point
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

	//emit the loop block's IR
    llvm::Value *lv = loop->EmitIR(state);

	//cast that to a proper BasicBlock
    llvm::BasicBlock *lvb = (llvm::BasicBlock*)lv;

	//create the post loop block
    llvm::BasicBlock *pl = llvm::BasicBlock::Create(state.context, "post_loop", current_function);

	//set the current insert point to the stored one
    state.builder.SetInsertPoint(current_insert);

    //state.builder.CreateBr(lvb);

	//emit the IR for the loop condition
    llvm::Value *eval_cond = cond_expr->EmitIR(state);

	//create a conditional branch using that loop condition
    state.builder.CreateCondBr(eval_cond, lvb, pl);

	//set the insert point to inside the loop
    state.builder.SetInsertPoint(lvb);

	//emit the IR for the loop condition
    eval_cond = cond_expr->EmitIR(state);

	//create another conditional branch
    state.builder.CreateCondBr(eval_cond, lvb, pl);

	//set the insert point to the post loop block
    state.builder.SetInsertPoint(pl);

	//do all the phi node nonsense
    llvm::PHINode *phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 2);
    phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), current_insert);
    phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 1), lvb);

    return pl;
}