#include <include/AST/Statement/ASTFunctionPointerDefinition.hpp>

ASTFunctionPointerDefinition::ASTFunctionPointerDefinition(ASTIdentifier &return_type, ASTIdentifier &id, std::vector<std::unique_ptr<ASTIdentifier>> &arg_types) : return_type(&return_type), id(&id), arg_types(&arg_types), ASTStatement(FUNCTION_PTR_DEFINITION) {}

llvm::Value *ASTFunctionPointerDefinition::EmitIR(IREmitter::EmitterState &state) 
{
	std::vector<llvm::Type *> types;

	for (auto &arg_t : *arg_types)
		types.push_back(state.typeRegistry.GetType(arg_t->identifier));

	state.typeRegistry.SetFunctionPointerType(id->identifier, types, return_type->identifier);

	return (llvm::Value*)state.typeRegistry.GetType(id->identifier);
}