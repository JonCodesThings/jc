#ifndef JC_ASTTYPESYSTEMMODSTATEMENT_H
#define JC_ASTTYPESYSTEMMODSTATEMENT_H

#include <include/AST/ASTStatement.hpp>

class ASTTypeSystemModStatement : public ASTStatement
{
public:
    enum TYPE_MOD_OP
    {
        ALIAS,
        TYPEDEF,
        TYPE_MOD_OP_COUNT
    } op;

    ASTTypeSystemModStatement(const TYPE_MOD_OP &op);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif