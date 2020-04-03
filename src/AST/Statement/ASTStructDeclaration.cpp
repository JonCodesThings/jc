#include <include/AST/Statement/ASTStructDeclaration.hpp>

ASTStructDeclaration::ASTStructDeclaration(ASTIdentifier &id) : id(&id) , ASTStatement(STRUCT_DECLARATION) {}

llvm::Value *ASTStructDeclaration::EmitIR(IREmitter::EmitterState &state)
{
	return nullptr;
}