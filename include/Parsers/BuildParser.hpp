#ifndef JC_BUILDPARSER_H
#define JC_BUILDPARSER_H

#include <include/Tokenizers/Tokenizer.hpp>
#include <include/Parsers/Parser.hpp>

#include <include/Build/BuildConfig.hpp>

class BuildParser : public Parser
{
public:
	BuildParser(BuildConfig &config);
	const bool Parse(const std::vector<Token> &tokens);

private:
	BuildConfig &config;
};

#endif