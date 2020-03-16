#ifndef JC_ASTTYPESYSTEMMODSTATEMENT_H
#define JC_ASTTYPESYSTEMMODSTATEMENT_H

#include <include/AST/ASTStatement.hpp>

/*!
* \brief AST Type System Modification Node
* Class for type system modification statements. No functionality implemented here currently
*/
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