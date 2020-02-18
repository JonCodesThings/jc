#ifndef JC_ASTNODE_H
#define JC_ASTNODE_H

#include <string>
#include <vector>

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <stdio.h>
#include <stdlib.h>

#include <include/IREmitter.hpp>


class ASTNode
{
public:
    unsigned int line_number;
    unsigned int start_char;

    ASTNode();
    virtual ~ASTNode();
    virtual const Symbol *GetSymbol(IREmitter::EmitterState &state);
    virtual const std::string *GetType(IREmitter::EmitterState &state);
    virtual llvm::Value *EmitIR(IREmitter::EmitterState &state) = 0;
};

#endif