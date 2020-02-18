#ifndef JC_ASTFUNCTIONDECLARATION_H
#define JC_ASTFUNCTIONDECLARATION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

class ASTFunctionDeclaration : public ASTStatement
{
public:
    ASTIdentifier &identifier;
    ASTIdentifier &return_type;
    ASTFunctionArgs &arguments;

    enum FUNCTION_LINKAGE
    {
        INTERNAL,
        EXTERN
    } linkage = EXTERN;

    ASTFunctionDeclaration();
    
    ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif