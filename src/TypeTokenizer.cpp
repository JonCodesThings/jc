#include <include/TypeTokenizer.hpp>

TypeTokenizer::TypeTokenizer() {}

TypeTokenizer::~TypeTokenizer() {}

std::vector<Token> TypeTokenizer::Tokenize(const std::string &in)
{
	std::vector<Token> tokens;
	std::string accum;
	std::string current_keyword;

	//very hacky way of dealing with type system modifications
	for (auto ch : in)
	{
		if (ch == '\t' || ch == ' ' || ch == '\n')
		{
			if (current_keyword.empty())
				continue;
		}

		accum.push_back(ch);

		if (accum == "typedef" || accum == "struct" || accum == "alias")
		{
			current_keyword = accum;
			Token t;
			if (accum == "typedef")
				t.token_type = TYPEDEF_T;
			else if (accum == "struct")
				t.token_type = STRUCT_T;
			else
				t.token_type = ALIAS_T;
			accum.clear();
			tokens.push_back(t);
		}
		else if ((accum.back() == ';' || accum.back() == '\n') && accum.length() > 1 && current_keyword.length() > 0)
		{
			accum.erase(accum.begin());
			accum.pop_back();
			std::string first = accum.substr(0, accum.find(" "));
			std::string second = accum.substr(accum.find(" ") + 1, accum.length() - 1);
			Token t1, t2;
			t2.token_type = t1.token_type = IDENTIFIER_T;
			t1.string = new std::string(first);
			t2.string = NULL;

			if (current_keyword == "typedef" || current_keyword == "alias")
				t2.string = new std::string(second);

			tokens.push_back(t1);

			if (t2.string != NULL)
				tokens.push_back(t2);
			current_keyword.clear();
		}
	}
	return tokens;
}