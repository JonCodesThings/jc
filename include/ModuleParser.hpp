#ifndef JC_MODULEPARSER_H
#define JC_MODULEPARSER_H

#include <include/Parser.hpp>
#include <include/TypeTokenizer.hpp>

class ModuleParser : public Parser
{
public:
	ModuleParser();
	~ModuleParser();

	const bool Parse(const std::vector<Token> &in);
};

#endif