#ifndef JC_ASTCONSTANTNULLPTR_H
#define JC_ASTCONSTANTNULLPTR_H

#include <include/AST/ASTConstant.hpp>

class ASTConstantNullptr : public ASTConstant
{
public:
	llvm::PointerType *nulltype = NULL;

	const std::string *nulltype_str = NULL;

	ASTConstantNullptr();

	llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const std::string *GetType(IREmitter::EmitterState &state);
};

#endif