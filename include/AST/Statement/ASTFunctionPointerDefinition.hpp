#ifndef JC_ASTFUNCPTRDEF_H
#define JC_ASTFUNCPTRDEF_H

#include <include/AST/ASTStatement.hpp>

#include <include/AST/Expression/ASTIdentifier.hpp>

class ASTFunctionPointerDefinition : public ASTStatement
{
public:
	std::unique_ptr<std::vector<std::unique_ptr<ASTIdentifier>>> arg_types;
	std::unique_ptr<ASTIdentifier> return_type;
	std::unique_ptr<ASTIdentifier> id;

	ASTFunctionPointerDefinition(ASTIdentifier &return_type, ASTIdentifier &id, std::vector<std::unique_ptr<ASTIdentifier>> &arg_types);
	llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif