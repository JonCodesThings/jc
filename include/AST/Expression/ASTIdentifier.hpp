#ifndef JC_ASTIDENTIFIER_H
#define JC_ASTIDENTIFIER_H

#include <include/AST/ASTExpression.hpp>

class ASTIdentifier : public ASTExpression
{
public:
    std::string identifier;

    ASTIdentifier(const std::string &identifier);

    ASTIdentifier();

    const std::string *GetType(IREmitter::EmitterState &state);

    const Symbol *GetSymbol(IREmitter::EmitterState &state);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif