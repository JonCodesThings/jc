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

#include "SymbolTableStack.hpp"
#include "TypeRegistry.hpp"

class ASTBlock;

/*!
* \brief Class used to traverse the Abstract Syntax tree and emit LLVM IR into a given module.
* 
*/
class IREmitter
{
public:
    struct EmitterState
    {
        EmitterState(llvm::Module &module, llvm::LLVMContext &context, TypeRegistry &r) 
        : module(module), context(context), builder(context), typeRegistry(r) {}
        llvm::Module &module;
        llvm::LLVMContext &context;
        llvm::IRBuilder<> builder;

        SymbolTableStack symbolStack;
        TypeRegistry &typeRegistry;
    };

    IREmitter(llvm::Module &module, llvm::LLVMContext &context, TypeRegistry &r) : state(module, context, r) {}
    bool EmitIR(ASTBlock *root);
    
private:
    EmitterState state;
};

#endif