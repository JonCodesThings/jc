#include <include/Tokenizers/TypeTokenizer.hpp>

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
		//printf("%s\n", accum.c_str());

		if (accum == "typedef" || accum == "struct" || accum == "alias" || accum == "func_ptr")
		{
			current_keyword = accum;
			Token t;
			if (accum == "typedef")
				t.token_type = TYPEDEF_T;
			else if (accum == "struct")
				t.token_type = STRUCT_T;
			else if (accum == "func_ptr")
				t.token_type = FUNC_PTR_T;
			else
				t.token_type = ALIAS_T;
			accum.clear();
			tokens.push_back(t);
		}
		else if ((accum.back() == ';' || accum.back() == '\n'))
		{
			if (accum.length() > 1 && current_keyword.length() > 0)
			{
				accum.erase(accum.begin());
				accum.pop_back();
				if (current_keyword == "typedef" || current_keyword == "alias")
				{
					std::string first = accum.substr(0, accum.find(' '));
					std::string second = accum.substr(accum.find(' ') + 1, accum.length() - 1);

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
				else if (current_keyword == "func_ptr")
				{
					std::string ret_type = accum.substr(0, accum.find(' '));

					std::string func_ptr_name = accum.substr(accum.find(' ') + 1, accum.find('(') - accum.find_first_of(' ') -1);

					std::string arg_types = accum.substr(accum.find('(') + 1, accum.find(')') - accum.find('(') - 1);

					std::vector<std::string> args;

					while (!arg_types.empty())
					{
						std::string sub;

						if (arg_types.find(',') != std::string::npos)
							sub = arg_types.substr(0, arg_types.find(","));
						else
							sub = arg_types;
						

						args.push_back(sub);
						//printf("%s\n", arg_types.c_str());
						if (arg_types.find(',') != std::string::npos)
							arg_types.erase(0, arg_types.find(",") + 1);
						else
							arg_types.clear();
					}

					Token t1, t2;
					t1.token_type = t2.token_type = IDENTIFIER_T;
					t1.string = new std::string(ret_type);
					t2.string = new std::string(func_ptr_name);
					tokens.push_back(t1);
					tokens.push_back(t2);

					for (auto arg : args)
					{
						Token t;
						t.token_type = IDENTIFIER_T;
						t.string = new std::string(arg);
						tokens.push_back(t);
					}
					current_keyword.clear();
				}
			}
			accum.clear();
		}
	}
	return tokens;
}