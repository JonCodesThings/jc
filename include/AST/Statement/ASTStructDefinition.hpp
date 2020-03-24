#ifndef JC_ASTSTRUCTDEFINITION_H
#define JC_ASTSTRUCTDEFINITION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>
#include <include/AST/Statement/ASTStructMemberDeclarations.hpp>

/*!
* \brief AST Struct Definition Node
* CAST Node representing the definition of a struct. Probably needs refactored
*/
class ASTStructDefinition : public ASTStatement
{
public:
    std::unique_ptr<ASTStructMemberDeclarations> contains;
    std::unique_ptr<ASTIdentifier> id;


    ASTStructDefinition(ASTIdentifier &id, ASTStructMemberDeclarations &contains);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif