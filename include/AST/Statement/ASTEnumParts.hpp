#ifndef JC_ASTENUMPARTS_H
#define JC_ASTENUMPARTS_H

#include <include/AST/Constant/ASTConstantInt.hpp>

#include <include/AST/Expression/ASTIdentifier.hpp>

struct ASTEnumPart
{
	std::unique_ptr<ASTIdentifier> id;
	std::unique_ptr<ASTConstantInt> val;

	ASTEnumPart(ASTIdentifier &id, ASTConstantInt *val);
};

struct ASTEnumParts
{
	std::vector<std::unique_ptr<ASTEnumPart>> parts;
};

#endif