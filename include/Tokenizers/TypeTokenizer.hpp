#ifndef JC_TYPETOKENIZER_H
#define JC_TYPETOKENIZER_H

#include <include/Tokenizers/Tokenizer.hpp>
#include <include/TypeRegistry.hpp>

class TypeTokenizer : public Tokenizer
{
public:
	enum TYPE_TOKENS
	{
		TYPEDEF_T,
		ALIAS_T,
		STRUCT_T,
		IDENTIFIER_T,
		FUNC_PTR_T,
		TYPE_TOKEN_COUNT
	};

	TypeTokenizer();
	~TypeTokenizer();

	std::vector<Token> Tokenize(const std::string &in);
};

#endif