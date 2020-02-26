#include <include/AST/Statement/ASTForStatement.hpp>

ASTForStatement::ASTForStatement(ASTStatement &first, ASTStatement &second, ASTStatement &third, ASTBlock &loop) :
    first(first), second(second), third(third), loop(loop), ASTStatement(FOR_STATEMENT) {}

llvm::Value *ASTForStatement::EmitIR(IREmitter::EmitterState &state)
{
    llvm::BasicBlock *current_insert = state.builder.GetInsertBlock();

    llvm::BasicBlock *pl = llvm::BasicBlock::Create(state.context, "post_loop", current_function);

    state.builder.SetInsertPoint(current_insert);

    llvm::Value *var = first.EmitIR(state);

    llvm::Value *loop_internals = loop.EmitIR(state);

    llvm::BasicBlock *lvb = (llvm::BasicBlock *)loop_internals;

    llvm::Value *loop_condition = second.EmitIR(state);
    llvm::Value *iterate = third.EmitIR(state);
    state.builder.CreateCondBr(loop_condition, lvb, pl);

    state.builder.SetInsertPoint(current_insert);
    llvm::Value *cond = second.EmitIR(state);
    state.builder.CreateCondBr(cond, lvb, pl);

    state.builder.SetInsertPoint(pl);

    llvm::PHINode *phi = state.builder.CreatePHI(llvm::Type::getInt8Ty(state.context), 2);
    phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 0), current_insert);
    phi->addIncoming(llvm::ConstantInt::get(llvm::Type::getInt8Ty(state.context), 1), lvb);

    return pl;
}