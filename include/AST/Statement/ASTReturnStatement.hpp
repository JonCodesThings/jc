#ifndef JC_ASTRETURNSTATEMENT_H
#define JC_ASTRETURNSTATEMENT_H

#include <include/AST/ASTStatement.hpp>

class ASTReturnStatement : public ASTStatement
{
public:
    ASTStatement *expr;

    ASTReturnStatement(ASTStatement &expr);
    
    llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif