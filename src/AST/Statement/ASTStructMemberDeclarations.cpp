#include <include/AST/Statement/ASTStructMemberDeclarations.hpp>

ASTStructMemberDeclaration::ASTStructMemberDeclaration(ASTIdentifier & type, ASTIdentifier & name, ASTNode * default_assign) : type(&type), name(&name), default_assign(default_assign) {}
