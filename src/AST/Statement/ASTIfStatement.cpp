#include <include/AST/Statement/ASTIfStatement.hpp>

ASTIfStatement::ASTIfStatement(ASTStatement &cond_expr, ASTBlock &then, ASTBlock *otherwise) : cond_expr(cond_expr), then(then), otherwise(otherwise) {}

llvm::Value *ASTIfStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::Value *eval_cond = cond_expr.EmitIR(state);

    llvm::Value *x = state.builder.CreateLoad(eval_cond);

    llvm::Value *v = state.builder.CreateICmpEQ(x, llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 1), "if_stmt");

    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

    auto merge = llvm::BasicBlock::Create(state.context, "merge", current_function);

    llvm::BasicBlock *th = (llvm::BasicBlock*)then.EmitIR(state);

    state.builder.CreateBr(merge);

    llvm::BasicBlock *ot;
    if (otherwise)
        ot = (llvm::BasicBlock*)otherwise->EmitIR(state);
    else
        ot = llvm::BasicBlock::Create(state.context, "otherwise", current_function);


    state.builder.SetInsertPoint(current_insert);

    llvm::BasicBlock *i = (llvm::BasicBlock*)th;

    state.builder.CreateCondBr(v, th, ot);

    state.builder.SetInsertPoint(ot);

    state.builder.CreateBr(merge);

    state.builder.SetInsertPoint(merge);

    auto Phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 0);
    Phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 1), th);

    if (otherwise)
        Phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), ot);

    return merge;
}