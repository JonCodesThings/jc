#ifndef JC_ASTINITIALIZERLIST_H
#define JC_ASTINITIALIZERLIST_H

#include <include/AST/ASTNode.hpp>
#include <vector>

class ASTInitializerList
{
public:
	std::unique_ptr<std::vector<std::unique_ptr<ASTNode>>> list;

	ASTInitializerList(std::vector<std::unique_ptr<ASTNode>> &list);
};

#endif