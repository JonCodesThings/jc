#ifndef JC_BUILDTOKENIZER_H
#define JC_BUILDTOKENIZER_H

#include <include/Tokenizers/Tokenizer.hpp>

#include <include/Build/BuildConfig.hpp>

class BuildTokenizer : public Tokenizer
{
public:
	enum BUILD_TOKEN
	{
		INCLUDE_T,
		IDENTIFIER_T,
		LINK_T,
		BUILD_TOKEN_COUNT
	};

	BuildTokenizer();
	std::vector<Token> Tokenize(const std::string &in);

};

#endif
