#include <include/AST/Expression/ASTFunctionCall.hpp>

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id) : identifier(&id), args(), ASTExpression(FUNCTION_CALL) {}

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id, std::vector<std::unique_ptr<ASTStatement>> &args) : identifier(&id), args(&args), ASTExpression(FUNCTION_CALL) {}


llvm::Value *ASTFunctionCall::EmitIR(IREmitter::EmitterState &state)
{
	if (!state.symbolStack.GetSymbolByIdentifier(identifier->identifier))
		return false;

	auto Func = state.symbolStack.GetSymbolByIdentifier(identifier->identifier)->function;

    
    std::vector<llvm::Value*> argvals;

    if (args)
    {
        for (auto &arg : *args)
            argvals.push_back(arg->EmitIR(state));
    }
    
    return state.builder.CreateCall(Func, argvals, identifier->identifier + "_call");
}

const std::string *ASTFunctionCall::GetType(IREmitter::EmitterState &state)
{
    const Symbol *s = state.symbolStack.GetSymbolByIdentifier(identifier->identifier);
    return state.typeRegistry.GetLifetimeTypeString(s->type);
}