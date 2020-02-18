#include <include/AST/Statement/ASTIfStatement.hpp>

ASTIfStatement::ASTIfStatement(ASTStatement &cond_expr, ASTBlock &then) : cond_expr(cond_expr), then(then) {}

llvm::Value *ASTIfStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::Value *eval_cond = cond_expr.EmitIR(state);

    llvm::Value *x = state.builder.CreateLoad(eval_cond);

    llvm::Value *v = state.builder.CreateICmpEQ(x, llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), 1), "if_stmt");

    prev_block = state.builder.GetInsertBlock();

    llvm::Value *th = then.EmitIR(state);

    auto el = llvm::BasicBlock::Create(state.context, "else", current_function);

    auto merge = llvm::BasicBlock::Create(state.context, "merge", current_function);

    //state.builder.CreateBr(merge);

    state.builder.SetInsertPoint(&current_function->getEntryBlock());

    llvm::BasicBlock *i = (llvm::BasicBlock*)th;

    state.builder.CreateCondBr(v, i, el);

    state.builder.SetInsertPoint(el);

    state.builder.CreateAlloca(state.typeRegistry.GetType("i8"), NULL, "yikes");

    state.builder.CreateBr(merge);

    state.builder.SetInsertPoint(merge);

    auto Phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 2);
    Phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 1), el);
    //Phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), el);

    return merge;
}