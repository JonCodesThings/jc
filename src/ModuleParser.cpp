#include <include/ModuleParser.hpp>

#include <include/ModuleTokenizer.hpp>

ModuleParser::ModuleParser()
{
}

ModuleParser::~ModuleParser()
{
}

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
