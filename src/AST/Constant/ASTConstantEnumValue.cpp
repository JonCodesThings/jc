#include <include/AST/Constant/ASTConstantEnumValue.hpp>

#include <include/AST/Constant/ASTConstantInt.hpp>

ASTConstantEnumValue::ASTConstantEnumValue(ASTIdentifier & type, ASTIdentifier & value) : type(&type), value(&value) {}

llvm::Value * ASTConstantEnumValue::EmitIR(IREmitter::EmitterState & state)
{
	const int *v = state.typeRegistry.GetEnumValue(type->identifier, value->identifier);

	if (!v)
		return nullptr;

	ASTConstantInt i(*v);
	return i.EmitIR(state);
}

const std::string *ASTConstantEnumValue::GetType(IREmitter::EmitterState &state)
{
	return state.typeRegistry.GetLifetimeTypeString(type->identifier);
}