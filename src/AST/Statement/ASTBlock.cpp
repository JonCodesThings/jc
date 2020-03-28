#include <include/AST/Statement/ASTBlock.hpp>

#include <include/AST/Statement/ASTDeferredStatement.hpp>
#include <include/AST/Statement/ASTFunctionDefinition.hpp>
#include <include/AST/Statement/ASTReturnStatement.hpp>

#include <algorithm>

#include <unordered_set>

ASTBlock::ASTBlock() : block(std::make_unique<std::vector<std::unique_ptr<ASTStatement>>>()), b(nullptr), ASTStatement(BLOCK) {}

ASTBlock::ASTBlock(std::vector<std::unique_ptr<ASTStatement>> &block) : block(&block), b(nullptr), ASTStatement(BLOCK) {}

bool ASTBlock::ContainsReturnStatement()
{
	//loop until we find a return statement
    for (auto &statement : *block)
    {
        if (statement)
        {
            if (statement->GetNodeType() == NODE_TYPE::RETURN_STATEMENT)
                return true;
        }
    }
    return false;
}

const std::string * ASTBlock::GetType(IREmitter::EmitterState & state)
{
	if (!ContainsReturnStatement())
		return nullptr;

	std::unordered_set<const std::string *>ret_types;

	for (auto &statement : *block)
	{
		if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
			ret_types.insert(statement->GetType(state));
	}

	if (ret_types.size() != 1)
		return nullptr;
	
	if (*ret_types.begin() == nullptr)
	{
		SyntheticEval(state);

		ret_types.clear();

		for (auto &statement : *block)
		{
			if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
				ret_types.insert(statement->GetType(state));
		}

		if (ret_types.size() != 1)
			return nullptr;
	}

	return *ret_types.begin();
}

//helper function to create a basic block and set it as the insert point
llvm::Value *ASTBlock::CreateBasicBlock(IREmitter::EmitterState &state, const std::string &name)
{
    b = llvm::BasicBlock::Create(state.context, name, current_function);

    state.builder.SetInsertPoint(b);

    return b;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state)
{
	//if we don't have a block create it
    if (!b)
        CreateBasicBlock(state, "new_block");

	//vectors of deferred and return statements
    std::vector<std::unique_ptr<ASTStatement>> deferred;
    std::vector<std::unique_ptr<ASTStatement>> r;

	//preprocess the block, removing redundant statements and adding them to the vectors as required
    for (auto &statement : *block)
    {
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::TYPE_MOD || statement->GetNodeType() == ASTNode::NODE_TYPE::IMPORT_STATEMENT || statement->GetNodeType() == ASTNode::NODE_TYPE::INCLUDE_STATEMENT || statement->GetNodeType() == ASTNode::NODE_TYPE::FUNCTION_PTR_DEFINITION)
        {
            delete statement.release();
            continue;
        }
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::DEFER_STATEMENT)
        {
            deferred.push_back(std::move(statement));
            statement.release();
            continue;
        }
        if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
        {
            r.push_back(std::move(statement));
            statement.release();
            continue;
        }
    }

	//loop through, downcast and move the deferred statement to the end of the block
    for (auto &s : deferred)
    {
        ASTDeferredStatement *casted = static_cast<ASTDeferredStatement*>(s.get());
        auto a = std::move(casted->defer);
        block->push_back(std::move(a));
    }

	//do the same with the return statements
    for (auto &s : r)
    {
        block->push_back(std::move(s));
    }

	//loop through and emit IR for all statements in the block
    for (auto &statement : *block)
    {
        if (statement)
        {
			if (statement->GetNodeType() == ASTNode::NODE_TYPE::FUNCTION_DEFINITION && current_function != nullptr)
			{
				ASTFunctionDefinition *def = (ASTFunctionDefinition*)statement.get();
				def->declaration->identifier->identifier = std::string(current_function->getName()) + "__" + def->declaration->identifier->identifier;
				auto current_insert = state.builder.GetInsertBlock();
				auto c = current_function;

				def->EmitIR(state);
				current_function = c;
				state.builder.SetInsertPoint(current_insert);

				continue;
			}
            if (!statement->EmitIR(state))
                return nullptr;
            if (statement->GetNodeType() == ASTNode::NODE_TYPE::RETURN_STATEMENT)
            {
                returned = true;
                break;
            }
        }
        
    }
    return b;
}

//this is for creating a function's entry block
llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args)
{        
	//create a basic block as normal
    CreateBasicBlock(state, "entry");

	//store all the argument values
    for (auto &arg : current_function->args())
    {
        Symbol *s = state.symbolStack.GetSymbolByIdentifier(arg.getName());
        s->alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(s->type), nullptr, arg.getName());
        state.builder.CreateStore(&arg, s->alloc_inst);
    }

	//emit the IR as normal
    auto ret = EmitIR(state);

	if (current_function->getReturnType() == state.typeRegistry.GetType("void"))
	{
		state.builder.CreateRetVoid();
	}

    return ret;
}

const bool ASTBlock::SyntheticEval(IREmitter::EmitterState & state)
{
	for (auto &statement : *block)
	{
		statement->SyntheticEval(state);
	}
	return true;
}