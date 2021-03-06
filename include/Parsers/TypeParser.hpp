#ifndef JC_TYPEPARSER_H
#define JC_TYPEPARSER_H

#include <include/Parsers/Parser.hpp>
#include <include/Tokenizers/TypeTokenizer.hpp>
#include <include/TypeRegistry.hpp>

class TypeParser : public Parser
{
public:
	TypeParser(TypeRegistry &registry);
	~TypeParser();

	const bool Parse(const std::vector<Token> &in);

private:
	TypeRegistry &registry;
};

#endif