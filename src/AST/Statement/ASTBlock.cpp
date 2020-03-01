#include <include/AST/Statement/ASTBlock.hpp>

#include <include/AST/Statement/ASTDeferredStatement.hpp>
#include <include/AST/Statement/ASTReturnStatement.hpp>

#include <algorithm>


ASTBlock::ASTBlock() : block(*new std::vector<ASTStatement*>()), b(NULL), ASTStatement(BLOCK) {}

ASTBlock::ASTBlock(std::vector<ASTStatement*> &block) : block(block), b(NULL), ASTStatement(BLOCK) {}

bool ASTBlock::ContainsReturnStatement()
{
    for (ASTStatement *statement : block)
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

    std::vector<ASTDeferredStatement*> deferred;
    std::vector<ASTReturnStatement*> r;

    for (ASTStatement *statement : block)
    {
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::DEFER_STATEMENT)
        {
            ASTDeferredStatement *s = (ASTDeferredStatement*)statement;
            deferred.push_back(s);
            continue;
        }
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
        {
            ASTReturnStatement *s = (ASTReturnStatement*)statement;
            r.push_back(s);
            continue;
        }
    }

    for (ASTStatement *s : deferred)
        block.erase(std::remove(block.begin(), block.end(), s), block.end());

    for (ASTReturnStatement *s : r)
        block.erase(std::remove(block.begin(), block.end(), s), block.end());

    for (ASTDeferredStatement *s : deferred)
        block.push_back(&s->defer);

    for (ASTReturnStatement *s : r)
        block.push_back(s);

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

    return EmitIR(state);
}