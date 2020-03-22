#include <include/Tokenizers/BuildTokenizer.hpp>

BuildTokenizer::BuildTokenizer() {}

std::vector<Token> BuildTokenizer::Tokenize(const std::string &in)
{
	std::string accum;
	std::string current_keyword;

	std::vector<Token> tokens;

	for (auto ch : in)
	{
		if (ch == '\t' || ch == ' ' || ch == '\n')
		{
			if (current_keyword.empty())
				continue;
		}

		accum.push_back(ch);

		if (accum == "include")
		{
			current_keyword = accum;

			Token t;
			t.token_type = INCLUDE_T;
			tokens.push_back(t);

			accum.clear();
			continue;
		}
		else if (accum == "link")
		{
			current_keyword = accum;

			Token t;
			t.token_type = LINK_T;
			tokens.push_back(t);

			accum.clear();
			continue;
		}

		if (ch == ';')
		{
			if (current_keyword == "include" || current_keyword == "link")
			{
				std::string path = accum;
				path = path.substr(path.find('\"') + 1, path.length() - 2);
				path = path.substr(0, path.find('\"'));

				Token t;
				t.token_type = IDENTIFIER_T;
				t.string = new std::string(path);

				current_keyword.clear();

				tokens.push_back(t);
			}
			accum.clear();
		}
	}

	return tokens;
}