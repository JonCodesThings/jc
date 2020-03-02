#ifndef JC_ASTFUNCTIONARGS_H
#define JC_ASTFUNCTIONARGS_H

#include <include/AST/Expression/ASTIdentifier.hpp>

struct ASTFunctionArg
{
    ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name);
    
    std::unique_ptr<ASTIdentifier> type;
    std::unique_ptr<ASTIdentifier> name;
};

class ASTFunctionArgs
{
public:
    std::vector<std::unique_ptr<ASTFunctionArg>> args;
};

#endif