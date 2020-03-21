#ifndef JC_MODULETOKENIZER_H
#define JC_MODULETOKENIZER_H

#include <include/Tokenizers/Tokenizer.hpp>
#include<include/TypeRegistry.hpp>

class ModuleTokenizer : public Tokenizer
{
public:
	enum MODULE_TOKENS
	{
		IMPORT_T,
		IDENTIFIER_T,
		MODULE_TOKENS_COUNT
	};

	ModuleTokenizer();
	~ModuleTokenizer();

	std::vector<Token> Tokenize(const std::string &in);
};

#endif