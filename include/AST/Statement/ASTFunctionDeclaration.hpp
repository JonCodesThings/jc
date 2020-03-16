#ifndef JC_ASTFUNCTIONDECLARATION_H
#define JC_ASTFUNCTIONDECLARATION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Expression/ASTIdentifier.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

/*!
* \brief AST Function Call Node
* AST Node that represents a function declaration. These are typically used for FFI with C.
*/
class ASTFunctionDeclaration : public ASTStatement
{
public:
    std::unique_ptr<ASTIdentifier> identifier;
    std::unique_ptr<ASTIdentifier> return_type;
    std::unique_ptr<ASTFunctionArgs> arguments;

    enum FUNCTION_LINKAGE
    {
        INTERNAL,
        EXTERN
    } linkage = EXTERN;
    
    ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif