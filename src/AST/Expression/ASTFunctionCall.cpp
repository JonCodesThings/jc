#include <include/AST/Expression/ASTFunctionCall.hpp>

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id) : identifier(id), args(NULL) {}

ASTFunctionCall::ASTFunctionCall(ASTIdentifier &id, std::vector<ASTStatement*> &args) : identifier(id), args(&args) {}


llvm::Value *ASTFunctionCall::EmitIR(IREmitter::EmitterState &state)
{
    auto Func = state.module.getFunction(identifier.identifier);
    
    std::vector<llvm::Value*> argvals;

    if (args)
    {
        for (auto &arg : *args)
            argvals.push_back(arg->EmitIR(state));
    }
    
    return state.builder.CreateCall(Func, argvals, identifier.identifier + "_call");
}