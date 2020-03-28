#include <include/AST/Statement/ASTIncludeStatement.hpp>

ASTIncludeStatement::ASTIncludeStatement(const std::string &s) : path(s), ASTStatement(INCLUDE_STATEMENT) {}

llvm::Value *ASTIncludeStatement::EmitIR(IREmitter::EmitterState &state)
{
	return nullptr;
}