#include <AST/Statement/ASTImportStatement.hpp>

ASTImportStatement::ASTImportStatement(ASTIdentifier &id) : id(&id), ASTStatement(IMPORT_STATEMENT) {}

llvm::Value *ASTImportStatement::EmitIR(IREmitter::EmitterState &state)
{
    
}