#ifndef JC_ASTFUNCTIONDEFINITION_H
#define JC_ASTFUNCTIONDEFINITION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>
#include <include/AST/Statement/ASTFunctionDeclaration.hpp>

class ASTFunctionDefinition : public ASTStatement
{
public:
    ASTFunctionDeclaration &declaration;
    ASTBlock &block;

    ASTFunctionDefinition();

    ASTFunctionDefinition(ASTIdentifier &id, ASTIdentifier &ret_type, ASTFunctionArgs &args, ASTBlock &block);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
    //ASTFunctionDefinition(ASTFunctionDeclaration &decl, ASTBlock &bl) :
    //declaration(decl), block(block) {}
};

#endif