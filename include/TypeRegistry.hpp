#ifndef JC_TYPE_REGISTRY_HPP
#define JC_TYPE_REGISTRY_HPP

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

#include <vector>

struct JCType
{
    std::string type_string;
    llvm::Type *llvm_type;

    enum TYPE_CLASSIFICATION
    {
        FLOAT,
        INT,
        CHAR,
        VOID,
        STRUCT
    } classification;
};

class TypeRegistry
{
public:

    TypeRegistry(llvm::LLVMContext &context) : context(context) {}
    ~TypeRegistry() {};
    void SetupBuiltinJCTypes();
    void AddType(const std::string &id, llvm::Type &type, const JCType::TYPE_CLASSIFICATION &classification);
    llvm::Type *GetType(const std::string &id);
    const std::string *GetLifetimeTypeString(const std::string &id);
private:
    llvm::LLVMContext &context;

    std::vector<JCType> registry;
};

#endif