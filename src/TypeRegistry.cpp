#include <include/TypeRegistry.hpp>

#include <stdio.h>

void TypeRegistry::SetupBuiltinJCTypes()
{
    AddType("void", *llvm::Type::getVoidTy(context), JCType::TYPE_CLASSIFICATION::VOID);

    AddType("i8", *llvm::Type::getInt8Ty(context), JCType::TYPE_CLASSIFICATION::INT, 127);
    AddType("i16", *llvm::Type::getInt16Ty(context), JCType::TYPE_CLASSIFICATION::INT, 32767);
    AddType("i32", *llvm::Type::getInt32Ty(context), JCType::TYPE_CLASSIFICATION::INT, 2147483647);

    AddType("u8", *llvm::Type::getInt8Ty(context), JCType::TYPE_CLASSIFICATION::INT, 127);
    AddType("u16", *llvm::Type::getInt16Ty(context), JCType::TYPE_CLASSIFICATION::INT, 32767);
    AddType("u32", *llvm::Type::getInt32Ty(context), JCType::TYPE_CLASSIFICATION::INT, 2147483647);

    AddType("f16", *llvm::Type::getHalfTy(context), JCType::TYPE_CLASSIFICATION::FLOAT);
    AddType("f32", *llvm::Type::getFloatTy(context), JCType::TYPE_CLASSIFICATION::FLOAT);
}

void TypeRegistry::AddAlias(const std::string &id, const std::string &type_to_be_aliased)
{
    const JCType *t = GetTypeInfo(type_to_be_aliased);
    if (!t)
        return;

    //printf("Alias generated to type_string: %s\n", t->type_string.c_str());

    alias_registry.push_back(std::make_pair(id, t->type_string));
}

void TypeRegistry::AddBlankStructType(const std::string &id)
{
    JCType type;
    type.type_string = id;
    type.classification = JCType::TYPE_CLASSIFICATION::STRUCT;

    registry.push_back(type);
}


void TypeRegistry::AddType(const std::string &id, llvm::Type &t, const JCType::TYPE_CLASSIFICATION &classification)
{
    JCType type;
    type.type_string = id;
    type.llvm_type = &t;
    type.classification = classification;

    registry.push_back(type);
}

void TypeRegistry::AddType(const std::string &id, llvm::Type &t, const JCType::TYPE_CLASSIFICATION &classification, unsigned int integer_upper_limit)
{
    JCType type;
    type.type_string = id;
    type.llvm_type = &t;
    type.classification = classification;
    type.INT_UPPER_LIMIT = integer_upper_limit;

    registry.push_back(type);
}

const std::string TypeRegistry::GetTypeStringFromAlias(const std::string &id)
{   
    for (auto &pair : alias_registry)
    {
        if (pair.first == id)
            return pair.second;
    }
    return "";
}

llvm::Type *TypeRegistry::GetAliasedType(const std::string &id)
{
    for (auto &pair : alias_registry)
    {
        if (pair.first == id)
            return GetType(pair.second);
    }
    return NULL;
}

llvm::Type *TypeRegistry::GetArrayType(const std::string &id, unsigned int array_size)
{
    return llvm::ArrayType::get(GetType(id), array_size);
}

llvm::Type *TypeRegistry::GetType(const std::string &id)
{
    auto t = GetAliasedType(id);

    if (t)
        return t;

    for (auto type_ : registry)
    {
        if (type_.type_string == id)
            return type_.llvm_type;
    }

    //llvm::Type * ptr_type = UnwindPointerType(id);

    return NULL;
}

llvm::Type *TypeRegistry::UnwindPointerType(const std::string &id)
{
    if (id[id.size() - 1] != '*')
        return GetType(id);
    else
    {
        llvm::Type *t = UnwindPointerType(id.substr(0, id.size() - 1));
        if (t)
            return llvm::PointerType::get(t, 0);
        else
        {
            return NULL;
        }
    }
    
}

const JCType *TypeRegistry::GetTypeInfo(const std::string &id)
{
    std::string search = id;
    std::string alias = GetTypeStringFromAlias(id);
    if (alias != "")
        search = alias;
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].type_string == search)
            return &registry[i];
    }
    return NULL;
}

const std::string *TypeRegistry::GetLifetimeTypeString(const std::string &id)
{
    std::string search = id;
    std::string alias = GetTypeStringFromAlias(id);
    if (alias != "")
        search = alias;
    //printf("%s\n", search.c_str());
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].type_string == search)
            return &registry[i].type_string;
    }
    return NULL;
}

void TypeRegistry::SetStructType(const std::string &id, const std::vector<llvm::Type *> &members)
{
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].type_string == id)
        {
            auto StructType = llvm::StructType::create(members, id);
            registry[i].llvm_type = StructType;
            return;
        }
    }
}

/*bool TypeRegistry::IsTypeNumeric(const JCType &type)
{
    return (type.classification == JCType::TYPE_CLASSIFICATION::INT || type.classification == JCType::TYPE_CLASSIFICATION::FLOAT || type.classification == JCType::TYPE_CLASSIFICATION::CHAR);
}*/

bool TypeRegistry::IsTypeNumeric(const std::string &id)
{
    std::string search = id;
    std::string alias = GetTypeStringFromAlias(id);
    if (alias != "")
        search = alias;
    JCType *t = NULL;
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].type_string == search)
            t = &registry[i];
    }

    if (t)
        return t->classification == JCType::TYPE_CLASSIFICATION::INT || t->classification == JCType::TYPE_CLASSIFICATION::FLOAT || t->classification == JCType::TYPE_CLASSIFICATION::CHAR;
    return false;
}

llvm::Type *TypeRegistry::GetNarrowingConversion(const std::string &current, const std::string &to)
{
    const std::string current_raw = GetTypeStringFromAlias(current);
    const std::string to_raw = GetTypeStringFromAlias(to);

    const JCType *curr = GetTypeInfo(current);
    const JCType *t = GetTypeInfo(to);

    if (current_raw != "")
        curr = GetTypeInfo(current_raw);

    if (to_raw != "")
        t = GetTypeInfo(to_raw);

    //printf("curr: %s   to: %s\n", curr->type_string.c_str(), t->type_string.c_str());


    if (curr->classification == JCType::TYPE_CLASSIFICATION::FLOAT)
        return t->llvm_type;

    if (curr->classification == JCType::TYPE_CLASSIFICATION::INT)
    {
        if (t->INT_UPPER_LIMIT <= curr->INT_UPPER_LIMIT)
            return t->llvm_type;
    }

    return NULL;
}

llvm::Type *TypeRegistry::GetWideningConversion(const std::string &current, const std::string &to)
{
    const std::string current_raw = GetTypeStringFromAlias(current);
    const std::string to_raw = GetTypeStringFromAlias(to);

    const JCType *curr = GetTypeInfo(current);
    const JCType *t = GetTypeInfo(to);

    if (current_raw != "")
        curr = GetTypeInfo(current_raw);

    if (to_raw != "")
        t = GetTypeInfo(to_raw);

    //printf("curr: %s   to: %s\n", curr->type_string.c_str(), t->type_string.c_str());

    if (curr->classification != JCType::TYPE_CLASSIFICATION::FLOAT && t->classification == JCType::TYPE_CLASSIFICATION::FLOAT)
        return t->llvm_type;

    if (curr->classification == JCType::TYPE_CLASSIFICATION::INT || curr->classification == JCType::TYPE_CLASSIFICATION::CHAR)
    {
        if (t->INT_UPPER_LIMIT >= curr->INT_UPPER_LIMIT)
            return t->llvm_type;
    }

    return NULL;
}

llvm::Type *TypeRegistry::GetImplicitCast(const std::string &current, const std::string &to)
{
    llvm::Type *t = GetWideningConversion(current, to);

    if (!t)
        return GetNarrowingConversion(current, to);

    return t;
}