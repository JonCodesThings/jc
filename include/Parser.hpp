#ifndef JC_PARSER_H
#define JC_PARSER_H

#include <vector>

#include <include/Tokenizer.hpp>

class Parser
{
public:
	virtual ~Parser();
	virtual const bool Parse(const std::vector<Token> &tokens) = 0;
};

#endif