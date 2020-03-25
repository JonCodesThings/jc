#include <include/AST/Constant/ASTConstantNullptr.hpp>

ASTConstantNullptr::ASTConstantNullptr() { node_type = NULLPTR; }

llvm::Value * ASTConstantNullptr::EmitIR(IREmitter::EmitterState & state)
{
	return llvm::ConstantPointerNull::get(nulltype);
}

const std::string * ASTConstantNullptr::GetType(IREmitter::EmitterState & state)
{
	return nulltype_str;
}