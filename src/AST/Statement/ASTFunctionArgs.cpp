#include <include/AST/Statement/ASTFunctionArgs.hpp>

ASTFunctionArg::ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name) : type(&type), name(&name) {}