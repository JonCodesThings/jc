#ifndef JC_ASTCONSTANTFLOAT_H
#define JC_ASTCONSTANTFLOAT_H

#include <include/AST/ASTConstant.hpp>

/*!
* \brief AST Constant Float Node
* Node that represents float constants
*/
class ASTConstantFloat : public ASTConstant
{
public:
    float constant;

    ASTConstantFloat(float constant);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);

    const std::string *GetType(IREmitter::EmitterState &state);
};

#endif