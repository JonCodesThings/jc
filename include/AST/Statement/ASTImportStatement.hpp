#ifndef JC_ASTIMPORTSTATEMENT_H
#define JC_ASTIMPORTSTATEMENT_H

#include <include/AST/ASTStatement.hpp>
#include <include/AST/Statement/ASTFunctionArgs.hpp>

class ASTImportStatement : public ASTStatement
{
public:
    std::unique_ptr<ASTIdentifier> id;

    ASTImportStatement(ASTIdentifier &id);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif