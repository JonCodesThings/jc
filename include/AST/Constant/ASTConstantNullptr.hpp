#ifndef JC_ASTCONSTANTnullptrPTR_H
#define JC_ASTCONSTANTnullptrPTR_H

#include <include/AST/ASTConstant.hpp>

class ASTConstantNullptr : public ASTConstant
{
public:
	llvm::PointerType *nullptr_type = nullptr;

	const std::string *nullptrtype_str = nullptr;

	ASTConstantNullptr();

	llvm::Value *EmitIR(IREmitter::EmitterState &state);

	const std::string *GetType(IREmitter::EmitterState &state);
};

#endif