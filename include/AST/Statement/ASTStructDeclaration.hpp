#ifndef JC_ASTSTRUCTDECLARATION_H
#define JC_ASTSTRUCTDECLARATION_H

#include <include/AST/ASTStatement.hpp>

#include <include/AST/Expression/ASTIdentifier.hpp>

class ASTStructDeclaration : public ASTStatement
{
public:
	std::unique_ptr<ASTIdentifier> id;

	ASTStructDeclaration(ASTIdentifier &id);

	llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif