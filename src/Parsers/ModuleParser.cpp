#include <include/Parsers/ModuleParser.hpp>

#include <include/Tokenizers/ModuleTokenizer.hpp>

ModuleParser::ModuleParser()
{
}

ModuleParser::~ModuleParser()
{
}

//TODO: Jon
//actually implement this
const bool ModuleParser::Parse(const std::vector<Token>& in)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (in.at(i).token_type == ModuleTokenizer::IMPORT_T)
		{

		}
	}
	return false;
}
