#ifndef JC_TOKENIZER_H
#define JC_TOKENIZER_H

#include <vector>

class Tokenizer
{
	virtual ~Tokenizer();
	virtual std::vector<int> Tokenize(const std::string &in) = 0;
};

#endif