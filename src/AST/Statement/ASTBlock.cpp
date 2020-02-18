#include <include/AST/Statement/ASTBlock.hpp>

ASTBlock::ASTBlock() : block(*new std::vector<ASTStatement*>()) {}

ASTBlock::ASTBlock(std::vector<ASTStatement*> &block) : block(block) {}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state)
{
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "temp", NULL);
    for (ASTStatement *statement : block)
    {
        if (!statement->EmitIR(state))
            return NULL;
    }
    return llvmBlock;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args, llvm::Function &func)
{        
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "entry", &func);
 
    state.builder.SetInsertPoint(llvmBlock);

    for (auto &arg : func.args())
    {
        Symbol *s = state.frontmost->GetSymbolByIdentifier(arg.getName());
        s->alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(s->type), NULL, arg.getName());
        state.builder.CreateStore(&arg, s->alloc_inst);
    }

    for (ASTStatement *statement : block)
    {
        if (!statement->EmitIR(state))
            return NULL;
    }
    return llvmBlock;
}