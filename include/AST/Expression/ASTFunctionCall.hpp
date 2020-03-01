#ifndef JC_ASTFUNCTIONCALL_H
#define JC_ASTFUNCTIONCALL_H

#include <include/AST/ASTExpression.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>

class ASTFunctionCall : public ASTExpression
{
public:
    std::unique_ptr<ASTIdentifier> identifier;
    std::unique_ptr<std::vector<ASTStatement*>> args;
    ASTFunctionCall(ASTIdentifier &id);
    ASTFunctionCall(ASTIdentifier &id, std::vector<ASTStatement*> &args);
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif