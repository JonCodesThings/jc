#include <include/AST/Expression/ASTFunctionCall.hpp>

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id) : identifier(&id), args(), ASTExpression(FUNCTION_CALL) {}

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id, std::vector<std::unique_ptr<ASTStatement>> &args) : identifier(&id), args(&args), ASTExpression(FUNCTION_CALL) {}


llvm::Value *ASTFunctionCall::EmitIR(IREmitter::EmitterState &state)
{
	const Symbol *s = state.symbolStack.GetSymbolByIdentifier(identifier->identifier);

	//if we can't find the function on the symbol table stack return nothing
	if (!s)
		return nullptr;

	//vector to store the argument values
	std::vector<llvm::Value*> argvals;

	//get the argument values by emitting the IR
	if (args)
	{
		for (auto &arg : *args)
		{
			if (arg->GetNodeType() == ASTNode::IDENTIFIER)
				argvals.push_back(state.builder.CreateLoad(arg->EmitIR(state), "load_var_value"));
			else
				argvals.push_back(arg->EmitIR(state));
		}
	}

	if (state.symbolStack.Top().GetSymbolByIdentifier(identifier->identifier) == s && s->classification == Symbol::Classification::FUNCTION)
	{
		for (auto arg : state.symbolStack.Top().GetSymbols())
		{
			if (arg.classification == Symbol::Classification::VARIABLE)
				argvals.push_back(state.builder.CreateLoad(arg.alloc_inst, "load_var_value"));
		}
	}

	if (s->classification == Symbol::Classification::FUNCTION)
	{
		//get the function for the symbol
		llvm::Function *func = s->function;

		if (func->getReturnType() == state.typeRegistry.GetType("void"))
		{
			return state.builder.CreateCall(func, argvals);
		}

		//add the call properly
		return state.builder.CreateCall(func, argvals, identifier->identifier + "_call");
	}
	else if (s->classification == Symbol::Classification::VARIABLE)
	{
		llvm::Value *v = state.builder.CreateLoad(s->alloc_inst, "funky_func");

		return state.builder.CreateCall(v, argvals, identifier->identifier + "_call");

	}
	return nullptr;
}

const std::string *ASTFunctionCall::GetType(IREmitter::EmitterState &state)
{
    const Symbol *s = state.symbolStack.GetSymbolByIdentifier(identifier->identifier);
    return state.typeRegistry.GetLifetimeTypeString(s->type);
}