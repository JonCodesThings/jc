#ifndef JC_ASTFUNCTIONARGS_H
#define JC_ASTFUNCTIONARGS_H

#include <include/AST/Expression/ASTIdentifier.hpp>

struct ASTFunctionArg
{
    ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name);
    ASTFunctionArg();
    
    std::unique_ptr<ASTIdentifier> type;
    std::unique_ptr<ASTIdentifier> name;
    bool variadic_arg = false;
};

class ASTFunctionArgs
{
public:
    std::vector<std::unique_ptr<ASTFunctionArg>> args;
};

#endif