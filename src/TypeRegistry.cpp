#include <include/TypeRegistry.hpp>

#include <include/AST/Statement/ASTStructMemberDeclarations.hpp>

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

	AddType("bool", *llvm::Type::getInt8Ty(context), JCType::TYPE_CLASSIFICATION::INT);
}

void TypeRegistry::AddAlias(const std::string &id, const std::string &type_to_be_aliased)
{
    const JCType *t = GetTypeInfo(type_to_be_aliased);
    if (!t)
        return;

    //printf("Alias generated to type_string: %s\n", t->type_string.c_str());

    alias_registry.push_back(std::make_pair(id, t->type_string));
}

void TypeRegistry::AddBlankEnumType(const std::string &id)
{
	JCType type;
	type.type_string = id;
	type.classification = JCType::TYPE_CLASSIFICATION::ENUM;

	type.llvm_type = GetType("i32");

	registry.push_back(type);
}

void TypeRegistry::AddBlankFunctionPointerType(const std::string & id)
{
	JCType type;
	type.type_string = id;
	type.classification = JCType::TYPE_CLASSIFICATION::POINTER;

	registry.push_back(type);
}

void TypeRegistry::AddBlankStructType(const std::string &id)
{
    JCType type;
    type.type_string = id;
    type.classification = JCType::TYPE_CLASSIFICATION::STRUCT;

    registry.push_back(type);
}

void TypeRegistry::AddBlankUnionType(const std::string &id)
{
	JCType type;
	type.type_string = id;
	type.classification = JCType::TYPE_CLASSIFICATION::UNION;

	registry.push_back(type);
}


void TypeRegistry::AddType(const std::string &id, llvm::Type &t, const JCType::TYPE_CLASSIFICATION &classification, const std::string &defined_in_module)
{
    JCType type;
    type.type_string = id;
    type.llvm_type = &t;
    type.classification = classification;
	type.CONTAINED_IN_MODULE = defined_in_module;

    registry.push_back(type);
}

void TypeRegistry::AddType(const std::string &id, llvm::Type &t, const JCType::TYPE_CLASSIFICATION &classification, unsigned int integer_upper_limit)
{
    JCType type;
    type.type_string = id;
    type.llvm_type = &t;
    type.classification = classification;
    type.INT_UPPER_LIMIT = integer_upper_limit;
	type.CONTAINED_IN_MODULE = "";

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
    return nullptr;
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

    for (auto &type_ : registry)
    {
        if (type_.type_string == id)
            return type_.llvm_type;
    }

	if (id.find('*') != std::string::npos)
	{
		llvm::Type * ptr_type = UnwindPointerType(id);
		AddType(id, *ptr_type, JCType::TYPE_CLASSIFICATION::POINTER);
		return ptr_type;
	}
    

    return nullptr;
}

llvm::Type * TypeRegistry::GetType(const std::string & id, const std::vector<std::string>& module_depends)
{
	auto t = GetTypeInfo(id);

	if (t != nullptr)
	{
		if (t->CONTAINED_IN_MODULE == "")
			return t->llvm_type;
		for (auto m : module_depends)
		{
			if (t->CONTAINED_IN_MODULE == m && t->EXPORTED)
				return t->llvm_type;
		}
	}
	return nullptr;
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
            return nullptr;
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
    return nullptr;
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
    return nullptr;
}

const std::string *TypeRegistry::GetLifetimeTypeString(llvm::FunctionType &type)
{
	std::string concrete;
	for (int i = 0; i < registry.size(); i++)
	{
		if (registry[i].llvm_type == llvm::PointerType::get(&type, 0))
		{
			concrete = registry[i].type_string;
			break;
		}
	}
	return GetLifetimeTypeString(concrete);
}

const int *TypeRegistry::GetEnumValue(const std::string &enum_id, const std::string &part_id)
{
	const JCType *t = GetTypeInfo(enum_id);

	if (!t)
		return nullptr;

	for (auto &val : t->ENUM_VALUES)
	{
		if (val.first == part_id)
			return &val.second;
	}
	return nullptr;
}

void TypeRegistry::SetEnumValues(const std::string &id,const std::vector<std::pair<std::string, int>> &enum_values, const std::string &define_in_module, bool exported)
{
	for (int i = 0; i < registry.size(); i++)
	{
		if (registry[i].type_string == id)
		{
			registry[i].ENUM_VALUES = enum_values;
			registry[i].CONTAINED_IN_MODULE = define_in_module;
			registry[i].EXPORTED = exported;
			return;
		}
	}
}

void TypeRegistry::SetFunctionPointerType(const std::string & id, const std::vector<llvm::Type*>& types, const std::string &ret_type, const std::string &define_in_module, bool exported)
{
	for (int i = 0; i < registry.size(); i++)
	{
		if (registry[i].type_string == id)
		{
			auto func_type = llvm::FunctionType::get(GetType(ret_type), types, false);
			auto ptr_type = llvm::PointerType::get(func_type, 0);
			registry[i].llvm_type = ptr_type;
			registry[i].CONTAINED_IN_MODULE = define_in_module;
			registry[i].EXPORTED = exported;
			return;
		}
	}
}

void TypeRegistry::SetStructType(const std::string &id, const std::vector<llvm::Type *> &members, const std::vector<std::string> &member_names, const std::vector<std::string> &member_typenames, const std::vector<llvm::Value*> &member_defaults, const std::string &define_in_module, bool exported)
{
    for (int i = 0; i < registry.size(); i++)
    {
        if (registry[i].type_string == id)
        {
            auto StructType = llvm::StructType::create(members, id);
            registry[i].llvm_type = StructType;
            registry[i].MEMBER_NAMES = member_names;
            registry[i].MEMBER_TYPENAMES = member_typenames;
			registry[i].MEMBER_DEFAULTS = member_defaults;
			registry[i].CONTAINED_IN_MODULE = define_in_module;
			registry[i].EXPORTED = exported;
            return;
        }
    }
}

void TypeRegistry::SetUnionType(const std::string & id, const std::vector<std::string>& member_names, const std::vector<std::string>& member_typenames, const std::string & largest_type, const std::string &define_in_module, bool exported)
{
	for (int i = 0; i < registry.size(); i++)
	{
		if (registry[i].type_string == id)
		{
			std::vector<llvm::Type*> t;
			t.push_back(GetType(largest_type));
			auto StructType = llvm::StructType::create(t, id);
			registry[i].llvm_type = StructType;
			registry[i].MEMBER_NAMES = member_names;
			registry[i].MEMBER_TYPENAMES = member_typenames;
			registry[i].CONTAINED_IN_MODULE = define_in_module;
			registry[i].EXPORTED = exported;
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
    JCType *t = nullptr;
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

    return nullptr;
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

    return nullptr;
}

llvm::Type *TypeRegistry::GetImplicitCast(const std::string &current, const std::string &to)
{
    llvm::Type *t = GetWideningConversion(current, to);

    if (!t)
        return GetNarrowingConversion(current, to);

    return t;
}