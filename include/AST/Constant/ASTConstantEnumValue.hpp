#ifndef JC_ASTCONSTANTENUMVALUE_H
#define JC_ASTCONSTANTENUMVALUE_H

#include <include/AST/ASTConstant.hpp>

#include <include/AST/Expression/ASTIdentifier.hpp>

class ASTConstantEnumValue : public ASTConstant
{
public:

	std::unique_ptr<ASTIdentifier> type;
	std::unique_ptr<ASTIdentifier> value;

	ASTConstantEnumValue(ASTIdentifier &type, ASTIdentifier &value);

	llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const std::string *GetType(IREmitter::EmitterState &state);
};

#endif