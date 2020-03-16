#ifndef JC_ASTIMPORTSTATEMENT_H
#define JC_ASTIMPORTSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

/*!
* \brief AST Import Statement Node
* Class for import statements. No functionality implemented here currently
*/
class ASTImportStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTIdentifier> id;

    ASTImportStatement();

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif