#ifndef JC_ASTCONSTANTSTRING_H
#define JC_ASTCONSTANTSTRING_H

#include <include/AST/ASTConstant.hpp>

class ASTConstantString : public ASTConstant
{
public:
    std::string constant;

    ASTConstantString(const std::string &constant);

    llvm::Value *EmitIR(IREmitter::EmitterState &state);

    const std::string *GetType(IREmitter::EmitterState &state);
};


#endif