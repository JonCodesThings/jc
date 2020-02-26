#include <include/AST/Statement/ASTBlock.hpp>

ASTBlock::ASTBlock() : block(*new std::vector<ASTStatement*>()), ASTStatement(BLOCK) {}

ASTBlock::ASTBlock(std::vector<ASTStatement*> &block) : block(block), ASTStatement(BLOCK) {}

bool ASTBlock::ContainsReturnStatement()
{
    for (ASTStatement *statement : block)
    {
        if (statement->GetNodeType() == NODE_TYPE::RETURN_STATEMENT)
            return true;
    }
    return false;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state)
{
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "temp", current_function);

    state.builder.SetInsertPoint(llvmBlock);

    for (ASTStatement *statement : block)
    {
        if (!statement->EmitIR(state))
            return NULL;
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
        {
            returned = true;
            break;
        }
    }
    b = llvmBlock;
    return llvmBlock;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args, llvm::Function &func)
{        
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "entry", &func);
 

    for (auto &arg : func.args())
    {
        Symbol *s = state.frontmost->GetSymbolByIdentifier(arg.getName());
        s->alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(s->type), NULL, arg.getName());
        state.builder.CreateStore(&arg, s->alloc_inst);
    }

    state.builder.SetInsertPoint(llvmBlock);

    for (ASTStatement *statement : block)
    {
        if (!statement->EmitIR(state))
            return NULL;
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
        {
            returned = true;
            break;
        }
    }
    b = llvmBlock;
    return llvmBlock;
}