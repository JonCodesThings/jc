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
        POINTER,
        STRUCT,
		ENUM,
		UNION
    } classification;

    unsigned int INT_UPPER_LIMIT;
    std::vector<std::string> MEMBER_NAMES;
    std::vector<std::string> MEMBER_TYPENAMES;
	std::vector<llvm::Value*> MEMBER_DEFAULTS;
	std::vector<std::pair<std::string, int>> ENUM_VALUES;
};

class TypeRegistry
{
public:

    TypeRegistry(llvm::LLVMContext &context) : context(context) {}
    ~TypeRegistry() {};
    void SetupBuiltinJCTypes();
    void AddAlias(const std::string &id, const std::string &type_to_be_aliased);
	void AddBlankEnumType(const std::string &id);
	void AddBlankFunctionPointerType(const std::string &id);
    void AddBlankStructType(const std::string &id);
	void AddBlankUnionType(const std::string &id);
    void AddType(const std::string &id, llvm::Type &type, const JCType::TYPE_CLASSIFICATION &classification);
    const std::string GetTypeStringFromAlias(const std::string &id);
    llvm::Type *GetAliasedType(const std::string &id);
    llvm::Type *GetArrayType(const std::string &id, unsigned int array_size);
    llvm::Type *GetType(const std::string &id);
    llvm::Type *UnwindPointerType(const std::string &id);
    const JCType *GetTypeInfo(const std::string &id);
    const std::string *GetLifetimeTypeString(const std::string &id);
	const std::string *GetLifetimeTypeString(llvm::FunctionType &type);
    //bool IsTypeNumeric(const JCType &type);
    bool IsTypeNumeric(const std::string &id);
	const int *GetEnumValue(const std::string &enum_id, const std::string &part_id);
    llvm::Type *GetWideningConversion(const std::string &current, const std::string &to);
    llvm::Type *GetNarrowingConversion(const std::string &current, const std::string &to);
    llvm::Type *GetImplicitCast(const std::string &current, const std::string &to);
	void SetEnumValues(const std::string &id, const std::vector<std::pair<std::string, int>> &enum_values);
	void SetFunctionPointerType(const std::string &id, const std::vector<llvm::Type*> &types, const std::string &ret_type);
    void SetStructType(const std::string &id, const std::vector<llvm::Type *> &members, const std::vector<std::string> &member_names, 
	const std::vector<std::string> &member_typenames, const std::vector<llvm::Value*> &member_defaults);
	void SetUnionType(const std::string &id, const std::vector<std::string> &member_names,
		const std::vector<std::string> &member_typenames, const std::string &largest_type);
private:
    void AddType(const std::string &id, llvm::Type &type, const JCType::TYPE_CLASSIFICATION &classification, unsigned int integer_limit);

    llvm::LLVMContext &context;

    std::vector<JCType> registry;

    std::vector<std::pair<std::string, std::string>> alias_registry;
};

#endif