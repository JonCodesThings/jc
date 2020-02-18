#include <include/AST/ASTNode.hpp>

llvm::Function *ASTNode::current_function = NULL;
llvm::BasicBlock *ASTNode::prev_block = NULL;

ASTNode::ASTNode() : line_number(0), start_char(0) {}

ASTNode::~ASTNode() {}

const Symbol *ASTNode::GetSymbol(IREmitter::EmitterState &state) { return NULL; }

const std::string *ASTNode::GetType(IREmitter::EmitterState &state) { return state.typeRegistry.GetLifetimeTypeString("void"); }