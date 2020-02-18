#ifndef JC_ASTCONSTANTFLOAT_H
#define JC_ASTCONSTANTFLOAT_H

#include <include/AST/ASTConstant.hpp>

class ASTConstantFloat : public ASTConstant
{
public:
    float constant;

    ASTConstantFloat(float constant);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);

    const std::string *GetType(IREmitter::EmitterState &state);
};

#endif