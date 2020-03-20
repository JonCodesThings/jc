#include <include/AST/Expression/ASTFunctionCall.hpp>

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id) : identifier(&id), args(), ASTExpression(FUNCTION_CALL) {}

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id, std::vector<std::unique_ptr<ASTStatement>> &args) : identifier(&id), args(&args), ASTExpression(FUNCTION_CALL) {}


llvm::Value *ASTFunctionCall::EmitIR(IREmitter::EmitterState &state)
{
	//if we can't find the function on the symbol table stack return nothing
	if (!state.symbolStack.GetSymbolByIdentifier(identifier->identifier))
		return NULL;

	//get the function for the symbol
	llvm::Function *func = state.symbolStack.GetSymbolByIdentifier(identifier->identifier)->function;
    
	//vector to store the argument values
    std::vector<llvm::Value*> argvals;

	//get the argument values by emitting the IR
    if (args)
    {
        for (auto &arg : *args)
            argvals.push_back(arg->EmitIR(state));
    }
    
	//add the call properly
    return state.builder.CreateCall(func, argvals, identifier->identifier + "_call");
}

const std::string *ASTFunctionCall::GetType(IREmitter::EmitterState &state)
{
    const Symbol *s = state.symbolStack.GetSymbolByIdentifier(identifier->identifier);
    return state.typeRegistry.GetLifetimeTypeString(s->type);
}