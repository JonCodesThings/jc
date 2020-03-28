#ifndef JC_ASTENUMDEFINITION_H
#define JC_ASTENUMDEFINITION_H

#include <include/AST/ASTStatement.hpp>

#include <include/AST/Expression/ASTIdentifier.hpp>

#include <include/AST/Statement/ASTEnumParts.hpp>

class ASTEnumDefinition : public ASTStatement
{
public:
	std::unique_ptr<ASTIdentifier> identifier;
	std::unique_ptr<ASTEnumParts> parts;


	ASTEnumDefinition(ASTIdentifier &identifier, ASTEnumParts &parts);

	llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const std::string *GetType(IREmitter::EmitterState &state);
};

#endif