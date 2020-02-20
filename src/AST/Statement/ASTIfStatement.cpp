#include <include/AST/Statement/ASTIfStatement.hpp>

ASTIfStatement::ASTIfStatement(ASTStatement &cond_expr, ASTBlock &then, ASTBlock *otherwise) : 
    cond_expr(cond_expr), then(then), otherwise(otherwise), ASTStatement(IF_STATEMENT) {}

llvm::Value *ASTIfStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::Value *eval_cond = cond_expr.EmitIR(state);

    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

    auto merge = llvm::BasicBlock::Create(state.context, "merge", current_function);

    llvm::BasicBlock *th = (llvm::BasicBlock*)then.EmitIR(state);

    if (!then.returned)
        state.builder.CreateBr(merge);

    llvm::BasicBlock *ot;
    if (otherwise)
        ot = (llvm::BasicBlock*)otherwise->EmitIR(state);
    else
        ot = llvm::BasicBlock::Create(state.context, "otherwise", current_function);


    state.builder.SetInsertPoint(current_insert);

    llvm::BasicBlock *i = (llvm::BasicBlock*)th;

    state.builder.CreateCondBr(eval_cond, th, ot);

    state.builder.SetInsertPoint(ot);

    if (otherwise)
    {
        if(!otherwise->returned)
            state.builder.CreateBr(merge);
    }
    else
        state.builder.CreateBr(merge);

    state.builder.SetInsertPoint(merge);

    llvm::PHINode *phi = NULL;

    if (!then.returned)
    {
        phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 0);
        phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 1), th);
    }

    if (otherwise)
    {
        if (!otherwise->returned)
            phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), ot);
    }
    else if (phi)
        phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), ot);

    return merge;
}