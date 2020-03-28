#include <include/AST/Constant/ASTConstantNullptr.hpp>

ASTConstantNullptr::ASTConstantNullptr() { node_type = NULLPTR; }

llvm::Value * ASTConstantNullptr::EmitIR(IREmitter::EmitterState & state)
{
	return llvm::ConstantPointerNull::get(nullptr_type);
}

const std::string * ASTConstantNullptr::GetType(IREmitter::EmitterState & state)
{
	return nullptrtype_str;
}