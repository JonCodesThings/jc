#include <include/Parsers/BuildParser.hpp>

#include <include/Tokenizers/BuildTokenizer.hpp>


BuildParser::BuildParser(BuildConfig &config) : config(config) {}

const bool BuildParser::Parse(const std::vector<Token> &tokens)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens.at(i).token_type == BuildTokenizer::INCLUDE_T)
		{
			config.AddModuleIncludeDirectory(*tokens.at(i + 1).string);
			config.AddModuleLibraryDirectory(*tokens.at(i + 1).string);
			delete tokens.at(i + 1).string;
			i++;
		}

		if (tokens.at(i).token_type == BuildTokenizer::LINK_T)
		{
			config.AddLibraryLink(*tokens.at(i + 1).string);
			delete tokens.at(i + 1).string;
			i++;
		}
	}

	return true;
}