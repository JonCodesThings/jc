#include <include/AST/Statement/ASTBlock.hpp>

#include <include/AST/Statement/ASTDeferredStatement.hpp>
#include <include/AST/Statement/ASTReturnStatement.hpp>

#include <algorithm>

ASTBlock::ASTBlock() : block(std::make_unique<std::vector<std::unique_ptr<ASTStatement>>>()), b(NULL), ASTStatement(BLOCK) {}

ASTBlock::ASTBlock(std::vector<std::unique_ptr<ASTStatement>> &block) : block(&block), b(NULL), ASTStatement(BLOCK) {}

bool ASTBlock::ContainsReturnStatement()
{
    for (auto &statement : *block)
    {
        if (statement->GetNodeType() == NODE_TYPE::RETURN_STATEMENT)
            return true;
    }
    return false;
}

llvm::Value *ASTBlock::CreateBasicBlock(IREmitter::EmitterState &state, const std::string &name)
{
    b = llvm::BasicBlock::Create(state.context, name, current_function);

    state.builder.SetInsertPoint(b);

    return b;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state)
{
    if (!b)
        CreateBasicBlock(state, "new_block");

    std::vector<std::unique_ptr<ASTStatement>> deferred;
    std::vector<std::unique_ptr<ASTStatement>> r;

    /*for (auto &statement : *block)
    {
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::DEFER_STATEMENT)
        {
            deferred.push_back(std::move(statement));
            continue;
        }
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
        {
            r.push_back(std::move(statement));
            continue;
        }
    }

    for (auto &s : deferred)
        block->erase(std::remove(block->begin(), block->end(), s), block->end());

    for (auto &s : r)
        block->erase(std::remove(block->begin(), block->end(), s), block->end());

    for (auto &s : deferred)
    {
        ASTDeferredStatement *casted = static_cast<ASTDeferredStatement*>(s.get());
        auto a = std::unique_ptr<ASTStatement>(&casted->defer);
        block->push_back(std::move(a));
    }

    for (auto &s : r)
    {
        ASTReturnStatement *casted = static_cast<ASTReturnStatement*>(s.get());
        auto a = std::unique_ptr<ASTStatement>(casted);
        block->push_back(std::move(a));
    }*/

    for (auto &statement : *block)
    {
        if (!statement->EmitIR(state))
            return NULL;
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
        {
            returned = true;
            break;
        }
    }
    return b;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args)
{        
    CreateBasicBlock(state, "entry");

    for (auto &arg : current_function->args())
    {
        Symbol *s = state.frontmost->GetSymbolByIdentifier(arg.getName());
        s->alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(s->type), NULL, arg.getName());
        state.builder.CreateStore(&arg, s->alloc_inst);
    }

    auto ret = EmitIR(state);

    return ret;
}