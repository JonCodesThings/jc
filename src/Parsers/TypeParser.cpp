#include <include/Parsers/TypeParser.hpp>

TypeParser::TypeParser(TypeRegistry &registry) : registry(registry) {}

TypeParser::~TypeParser() {}

const bool TypeParser::Parse(const std::vector<Token> &in)
{
	//this is another hacked together parsing pass to add types to the type registry
	for (int i = 0; i < in.size(); i++)
	{
		switch (in.at(i).token_type)
		{
		default:
			break;
		case TypeTokenizer::TYPEDEF_T:
		{
			if (i + 1 < in.size())
			{
				const JCType *t = registry.GetTypeInfo(*in.at(i + 1).string);

				if (i + 2 < in.size())
					registry.AddType(*in.at(i + 2).string, *t->llvm_type, t->classification);
			}
			break;
		}
		case TypeTokenizer::ALIAS_T:
		{
			if (i + 1 < in.size())
			{
				const JCType *t = registry.GetTypeInfo(*in.at(i + 1).string);

				if (i + 2 < in.size())
					registry.AddAlias(*in.at(i + 2).string, *in.at(i + 1).string);
			}
			break;
		}
		case TypeTokenizer::STRUCT_T:
		{
			if (i + 1 < in.size())
			{
				registry.AddBlankStructType(*in.at(i + 1).string);
			}
			break;
		}
		case TypeTokenizer::UNION_T:
		{
			if (i + 1 < in.size())
			{
				registry.AddBlankUnionType(*in.at(i + 1).string);
			}
			break;
		}
		case TypeTokenizer::ENUM_T:
		{
			if (i + 1 < in.size())
			{
				registry.AddBlankEnumType(*in.at(i + 1).string);
			}
			break;
		}
		case TypeTokenizer::IDENTIFIER_T:
		{
			delete in.at(i).string;
			break;
		}
		case TypeTokenizer::FUNC_PTR_T:
		{
			std::string ret_type = *in.at(i + 1).string;
			delete in.at(i + 1).string;

			std::string type_n = *in.at(i + 2).string;
			delete in.at(i + 2).string;

			i += 2;

			registry.AddBlankFunctionPointerType(type_n);
		}
		}
	}
	return false;
}
