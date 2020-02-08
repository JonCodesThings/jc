#ifndef JC_IREMITTER_H
#define JC_IREMITTER_H

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

#include "SymbolTable.hpp"
#include "TypeRegistry.hpp"

class ASTBlock;

class IREmitter
{
public:
    struct EmitterState
    {
        EmitterState(llvm::Module &module, llvm::LLVMContext &context) : module(module), context(context), builder(context), typeRegistry(context) {}
        llvm::Module &module;
        llvm::LLVMContext &context;
        llvm::IRBuilder<> builder;

        SymbolTable symbolTable;
        TypeRegistry typeRegistry;
    };

    IREmitter(llvm::Module &module, llvm::LLVMContext &context) : state(module, context) {}
    bool EmitIR(ASTBlock *root);
    
private:
    EmitterState state;
};

#endif