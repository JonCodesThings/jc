#include <include/TypeRegistry.hpp>

#include <stdio.h>

void TypeRegistry::SetupBuiltinJCTypes()
{
    AddType("void", *llvm::Type::getVoidTy(context), JCType::TYPE_CLASSIFICATION::VOID);

    AddType("i8", *llvm::Type::getInt8Ty(context), JCType::TYPE_CLASSIFICATION::INT);
    AddType("i16", *llvm::Type::getInt16Ty(context), JCType::TYPE_CLASSIFICATION::INT);
    AddType("i32", *llvm::Type::getInt32Ty(context), JCType::TYPE_CLASSIFICATION::INT);

    AddType("u8", *llvm::Type::getInt8Ty(context), JCType::TYPE_CLASSIFICATION::INT);
    AddType("u16", *llvm::Type::getInt16Ty(context), JCType::TYPE_CLASSIFICATION::INT);
    AddType("u32", *llvm::Type::getInt32Ty(context), JCType::TYPE_CLASSIFICATION::INT);
}

void TypeRegistry::AddType(const std::string &id, llvm::Type &t, const JCType::TYPE_CLASSIFICATION &classification)
{
    JCType type;
    type.type_string = id;
    type.llvm_type = &t;
    type.classification = classification;

    registry.push_back(type);
}

llvm::Type *TypeRegistry::GetType(const std::string &id)
{
    for (auto type_ : registry)
    {
        if (type_.type_string == id)
            return type_.llvm_type;
    }
    return NULL;
}

const std::string *TypeRegistry::GetLifetimeTypeString(const std::string &id)
{
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].type_string == id)
            return &registry[i].type_string;
    }
    return NULL;
}