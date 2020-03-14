#ifndef JC_TOKENIZER_H
#define JC_TOKENIZER_H

#include <string>
#include <vector>

struct Token
{
	int token_type;
	union
	{
		std::string *string;
	};
};

class Tokenizer
{
public:
	virtual ~Tokenizer();
	virtual std::vector<Token> Tokenize(const std::string &in) = 0;
};

#endif
