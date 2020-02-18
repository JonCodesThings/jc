#include <include/AST/ASTNode.hpp>

ASTNode::ASTNode() : line_number(0), start_char(0) {}

ASTNode::~ASTNode() {}

const Symbol *ASTNode::GetSymbol(IREmitter::EmitterState &state) { return NULL; }

const std::string *ASTNode::GetType(IREmitter::EmitterState &state) { return state.typeRegistry.GetLifetimeTypeString("void"); }