#include <include/AST/Statement/ASTImportStatement.hpp>

ASTImportStatement::ASTImportStatement() : ASTStatement(IMPORT_STATEMENT) {}

llvm::Value *ASTImportStatement::EmitIR(IREmitter::EmitterState &state)
{
	return nullptr;
}