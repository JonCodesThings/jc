#include <include/AST/Expression/ASTFunctionCall.hpp>

#include <include/AST/Expression/ASTUnaryOperator.hpp>

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
			{
				const Symbol *sy = arg->GetSymbol(state);
				if (sy->array_size > 1)
				{
					llvm::Value *v = state.builder.CreateGEP(state.typeRegistry.GetArrayType(sy->type.substr(0, sy->type.length() - 1), sy->array_size), sy->alloc_inst, { llvm::ConstantInt::get(state.typeRegistry.GetType("i32"), 0), llvm::ConstantInt::get(state.typeRegistry.GetType("i32"), 0) });
					argvals.push_back(v);
					//printf("Adding symbol %s with type %s to function %s's argument values.\n", sy->identifier.c_str(), sy->type.c_str(), s->identifier.c_str());
				}
				else
				{
					argvals.push_back(state.builder.CreateLoad(arg->EmitIR(state), "load_var_value"));
					//printf("Adding symbol %s with type %s to function %s's argument values.\n", sy->identifier.c_str(), sy->type.c_str(), s->identifier.c_str());
				}
			}
			else
			{
				argvals.push_back(arg->EmitIR(state));
				//printf("Adding an argument with type %s to function %s's argument values.\n", arg->GetType(state)->c_str(), s->identifier.c_str());
			}
		}
	}

	//if (state.symbolStack.Top().GetSymbolByIdentifier(identifier->identifier) == s && s->classification == Symbol::Classification::FUNCTION)
	//{
	//	for (auto arg : state.symbolStack.Top().GetSymbols())
	//	{
	//		if (arg.classification == Symbol::Classification::VARIABLE)
	//			argvals.push_back(state.builder.CreateLoad(arg.alloc_inst, "load_var_value"));
	//	}
	//}
	if (s->classification == Symbol::Classification::FUNCTION && s->nested_func)
	{
		//printf("Symbol stack size: %zd\n", state.symbolStack.Size());

		auto it = s->function->args().begin();
		if (args)
			it += args->size();
		for (it; it != s->function->args().end(); it++)
		{
			std::string symname = (*it).getName();
			const Symbol *sym = state.symbolStack.GetSymbolByIdentifier(symname);
			if (!sym)
				continue;
			llvm::Value *v = sym->alloc_inst;
			//printf("Adding symbol %s with type %s to nested function %s's argument values.\n", symname.c_str(), sym->type.c_str(), s->identifier.c_str());
			argvals.push_back(state.builder.CreateLoad(v));
		}
	}

	if (s->classification == Symbol::Classification::FUNCTION)
	{
		//get the function for the symbol
		llvm::Function *func = s->function;

		if (func->getReturnType() == state.typeRegistry.GetType("void"))
		{
			//state.module->print(llvm::errs(), nullptr);
			//printf("Calling function %s with %d arguments!\n", s->identifier.c_str(), argvals.size());
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