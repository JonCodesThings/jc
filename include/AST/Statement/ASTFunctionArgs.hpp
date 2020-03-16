#ifndef JC_ASTFUNCTIONARGS_H
#define JC_ASTFUNCTIONARGS_H

#include <include/AST/Expression/ASTIdentifier.hpp>

/*!
* \brief AST Function Args
* Struct for representing function arguments
*/
struct ASTFunctionArg
{
    ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name);
    ASTFunctionArg();
    
    std::unique_ptr<ASTIdentifier> type;
    std::unique_ptr<ASTIdentifier> name;
    bool variadic_arg = false;
};


/*!
* \brief AST Function Args
* Class for representing a complete set of function arguments. Contains a std::vector.
*/
class ASTFunctionArgs
{
public:
    std::vector<std::unique_ptr<ASTFunctionArg>> args;
};

#endif