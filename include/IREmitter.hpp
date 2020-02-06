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

#include "AST.hpp"

class IREmitter
{
IREmitter(llvm::Module &module, llvm::LLVMContext &context) : module(module), context(context) {}
bool EmitIR(ASTBlock &root)
{
for (auto statement : root.block)
{
statement->EmitIR();
}
}
private:
llvm::Module &module;
llvm::LLVMContext &context;
llvm::IRBuilder<> builder;
};
