#include <include/AST/ASTNode.hpp>

llvm::Function *ASTNode::current_function = nullptr;

ASTNode::ASTNode(const NODE_TYPE &type) : line_number(0), start_char(0), node_type(type) {}

ASTNode::~ASTNode() {}

const Symbol *ASTNode::GetSymbol(IREmitter::EmitterState &state) { return nullptr; }

const std::string *ASTNode::GetType(IREmitter::EmitterState &state) { return state.typeRegistry.GetLifetimeTypeString("void"); }

const ASTNode::NODE_TYPE ASTNode::GetNodeType() { return node_type; }

const bool ASTNode::SyntheticEval(IREmitter::EmitterState &state) { return false; }