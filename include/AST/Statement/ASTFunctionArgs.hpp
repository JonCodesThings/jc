#ifndef JC_ASTFUNCTIONARGS_H
#define JC_ASTFUNCTIONARGS_H

#include <include/AST/Expression/ASTIdentifier.hpp>

struct ASTFunctionArg
{
    ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name);
    
    ASTIdentifier &type;
    ASTIdentifier &name;
};

class ASTFunctionArgs
{
public:
    std::vector<ASTFunctionArg> args;
};

#endif