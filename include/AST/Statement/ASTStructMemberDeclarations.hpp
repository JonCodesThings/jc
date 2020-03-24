#ifndef JC_ASTSTRUCTMEMBERDECLARATIONS_H
#define JC_ASTSTRUCTMEMBERDECLARATIONS_H

#include <include/AST/Expression/ASTIdentifier.hpp>

struct ASTStructMemberDeclaration
{
	ASTStructMemberDeclaration(ASTIdentifier &type, ASTIdentifier &member_name, ASTNode *default_assign);

	std::unique_ptr<ASTIdentifier> type;
	std::unique_ptr<ASTIdentifier> name;
	std::unique_ptr<ASTNode> default_assign;
};

class ASTStructMemberDeclarations
{
public:
	std::vector<std::unique_ptr<ASTStructMemberDeclaration>> args;
};

#endif