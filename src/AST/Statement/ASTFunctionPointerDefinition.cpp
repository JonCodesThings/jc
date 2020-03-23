#include <include/AST/Statement/ASTFunctionPointerDefinition.hpp>

ASTFunctionPointerDefinition::ASTFunctionPointerDefinition() : ASTStatement(FUNCTION_PTR_DEFINITION) {}

llvm::Value *ASTFunctionPointerDefinition::EmitIR(IREmitter::EmitterState &state) { return NULL; }