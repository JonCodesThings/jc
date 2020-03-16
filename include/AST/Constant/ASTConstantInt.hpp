#ifndef JC_ASTCONSTANTINT_H
#define JC_ASTCONSTANTINT_H

#include <include/AST/ASTConstant.hpp>

/*!
* \brief AST Constant Int Node
* Class for AST Nodes representing constant integers
*/
class ASTConstantInt : public ASTConstant
{
public:
    int constant;

    ASTConstantInt(int constant);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);

    const std::string *GetType(IREmitter::EmitterState &state);
};

#endif