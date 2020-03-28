#ifndef JC_ASTUNIONDEFINITION_H
#define JC_ASTUNIONDEFINITION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>
#include <include/AST/Statement/ASTStructMemberDeclarations.hpp>

class ASTUnionDefinition : public ASTStatement
{
public:
	std::unique_ptr<ASTStructMemberDeclarations> contains;
	std::unique_ptr<ASTIdentifier> id;


	ASTUnionDefinition(ASTIdentifier &id, ASTStructMemberDeclarations &contains);

	llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif