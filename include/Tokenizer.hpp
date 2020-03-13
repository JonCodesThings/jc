#ifndef JC_TOKENIZER_H
#define JC_TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer
{
public:
	virtual ~Tokenizer();
	virtual std::vector<int> Tokenize(const std::string &in) = 0;
};

#endif