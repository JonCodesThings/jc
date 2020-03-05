#ifndef JC_ASTSTRUCTDEFINITION_H
#define JC_ASTSTRUCTDEFINITION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

class ASTStructDefinition : public ASTStatement
{
public:
    std::unique_ptr<ASTFunctionArgs> contains;
    std::unique_ptr<ASTIdentifier> id;


    ASTStructDefinition(ASTIdentifier &id, ASTFunctionArgs &contains);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif