#ifndef JC_ASTFUNCTIONDEFINITION_H
#define JC_ASTFUNCTIONDEFINITION_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTBlock.hpp>
#include <include/AST/Statement/ASTFunctionDeclaration.hpp>

/*!
* \brief AST Function Call Node
* AST Node that represents a function definition
*/
class ASTFunctionDefinition : public ASTStatement
{
public:
    std::unique_ptr<ASTFunctionDeclaration> declaration;
    std::unique_ptr<ASTBlock> block;
	std::unique_ptr<ASTIdentifier> id;
	std::unique_ptr<ASTIdentifier> return_type;
	std::unique_ptr<ASTFunctionArgs> args;
	bool exporting = false;


    ASTFunctionDefinition(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args, ASTBlock &block);
	ASTFunctionDefinition(ASTIdentifier &id, ASTFunctionArgs &args, ASTBlock &block);


    llvm::Value *EmitIR(IREmitter::EmitterState &state);

	void SetExporting(const bool expa);
};

#endif