#include <include/TypeRegistry.hpp>

#include <stdio.h>

void TypeRegistry::SetupBuiltinJCTypes()
{
    AddType("void", *llvm::Type::getVoidTy(context));

    AddType("i8", *llvm::Type::getInt8Ty(context));
    AddType("i16", *llvm::Type::getInt16Ty(context));
    AddType("i32", *llvm::Type::getInt32Ty(context));

    AddType("u8", *llvm::Type::getInt8Ty(context));
    AddType("u16", *llvm::Type::getInt16Ty(context));
    AddType("u32", *llvm::Type::getInt32Ty(context));

    AddType("void", *llvm::Type::getVoidTy(context));
}

void TypeRegistry::AddType(const std::string &id, llvm::Type &type)
{
    auto type_ = std::make_pair(id, &type);

    registry.push_back(type_);
}

llvm::Type *TypeRegistry::GetType(const std::string &id)
{
    for (auto type_ : registry)
    {
        if (type_.first == id)
            return type_.second;
    }
    return NULL;
}

const std::string *TypeRegistry::GetLifetimeTypeString(const std::string &id)
{
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].first == id)
            return &registry[i].first;
    }
    return NULL;
}