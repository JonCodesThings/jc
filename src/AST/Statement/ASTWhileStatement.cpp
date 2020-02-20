#include <include/AST/Statement/ASTWhileStatement.hpp>

ASTWhileStatement::ASTWhileStatement(ASTStatement &cond_expr, ASTBlock &loop) : cond_expr(cond_expr), loop(loop), ASTStatement(WHILE_STATEMENT) {}

llvm::Value *ASTWhileStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::BasicBlock *l = llvm::BasicBlock::Create(state.context, "loop", current_function);

    state.builder.SetInsertPoint(l);

    llvm::Value *lv = loop.EmitIR(state);

    cond_expr.EmitIR(state);

    l = llvm::BasicBlock::Create(state.context, "post_loop", current_function);

    state.builder.SetInsertPoint(l);

}
