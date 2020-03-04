#include <include/AST/Statement/ASTFunctionArgs.hpp>

ASTFunctionArg::ASTFunctionArg(ASTIdentifier &type, ASTIdentifier &name) : type(&type), name(&name), variadic_arg(false) {}

ASTFunctionArg::ASTFunctionArg() : type(), name(), variadic_arg(true) {}