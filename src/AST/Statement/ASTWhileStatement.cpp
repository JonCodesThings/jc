#include <include/AST/Statement/ASTWhileStatement.hpp>

ASTWhileStatement::ASTWhileStatement(ASTStatement &cond_expr, ASTBlock &loop) : cond_expr(cond_expr), loop(loop), ASTStatement(WHILE_STATEMENT) {}

llvm::Value *ASTWhileStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

    llvm::Value *lv = loop.EmitIR(state);

    llvm::BasicBlock *lvb = (llvm::BasicBlock*)lv;

    state.builder.SetInsertPoint(current_insert);

    state.builder.CreateBr(lvb);

    state.builder.SetInsertPoint(lvb);

    llvm::Value *eval_cond = cond_expr.EmitIR(state);

    llvm::BasicBlock *pl = llvm::BasicBlock::Create(state.context, "post_loop", current_function);

    state.builder.CreateCondBr(eval_cond, lvb, pl);

    state.builder.SetInsertPoint(pl);

    return pl;
}
