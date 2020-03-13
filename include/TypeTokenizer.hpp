#ifndef JC_TYPETOKENIZER_H
#define JC_TYPETOKENIZER_H

#include <include/Tokenizer.hpp>
#include<include/TypeRegistry.hpp>

class TypeTokenizer : public Tokenizer
{
public:
	enum TYPE_TOKENS
	{
		TYPEDEF_T,
		ALIAS_T,
		STRUCT_T,
		TYPE_TOKEN_COUNT
	};

	TypeTokenizer(TypeRegistry &registry);
	~TypeTokenizer();

	std::vector<int> Tokenize(const std::string &in);

private:
	TypeRegistry &registry;
};

#endif