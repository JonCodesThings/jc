#ifndef JC_ASTINCLUDESTATEMENT_H
#define JC_ASTINCLUDESTATEMENT_H

#include <include/AST/ASTStatement.hpp>

/*!
* \brief AST Include Statement Node
* Class for include statements. No functionality implemented here currently
*/
class ASTIncludeStatement : public ASTStatement
{
public:
	std::string path;

	ASTIncludeStatement(const std::string &path);

	llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif