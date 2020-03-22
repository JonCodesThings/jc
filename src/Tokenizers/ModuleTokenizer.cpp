#include <include/Tokenizers/ModuleTokenizer.hpp>

#include <fstream>

ModuleTokenizer::ModuleTokenizer() {}
ModuleTokenizer::~ModuleTokenizer() {}

std::vector<Token> ModuleTokenizer::Tokenize(const std::string &in)
{
	std::vector<Token> tokens;
	std::string accum;
	bool importing = false;

	//very much hacked together way of doing this
	for (auto ch : in)
	{
		if (ch == '\t' || ch == ' ' || ch == '\n')
		{
			if (!importing)
				continue;
		}

		accum.push_back(ch);
		//printf("%s\n", accum.c_str());

		if (accum == "import")
		{
			Token t;
			t.token_type = IMPORT_T;
			t.string = NULL;
			tokens.push_back(t);
			importing = true;
			accum.clear();
			continue;
		}

		if (accum.back() == ';' && accum.length() > 1 && importing)
		{
			accum.erase(accum.begin());
			accum.pop_back();


			//std::ifstream imp(accum + ".jc");
			//std::string *import_contents = new std::string((std::istreambuf_iterator<char>(imp)), std::istreambuf_iterator<char>());
			//imp.close();

			Token t;
			t.token_type = IDENTIFIER_T;
			t.string = new std::string(accum + ".jc");
			tokens.push_back(t);
			importing = false;
			accum.clear();
			continue;
		}
		else if (accum.back() == ';')
			accum.clear();
	}

	return tokens;
}