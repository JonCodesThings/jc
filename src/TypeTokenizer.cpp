#include <include/TypeTokenizer.hpp>

TypeTokenizer::TypeTokenizer(TypeRegistry &registry) : registry(registry) {}

TypeTokenizer::~TypeTokenizer() {}

std::vector<int> TypeTokenizer::Tokenize(const std::string &in)
{
	std::vector<int> tokens;
	std::string accum;
	std::string current_keyword;

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
			accum.clear();
		}
		else if ((accum.back() == ';' || accum.back() == '\n') && accum.length() > 1 && current_keyword.length() > 0)
		{
			accum.erase(accum.begin());
			accum.pop_back();
			std::string first = accum.substr(0, accum.find(" "));
			std::string second = accum.substr(accum.find(" ") + 1, accum.length() - 1);
			if (current_keyword == "typedef")
			{

				const JCType *t = registry.GetTypeInfo(first);
				registry.AddType(accum, *t->llvm_type, t->classification);
			}
			else if (current_keyword == "alias")
			{
				const JCType *t = registry.GetTypeInfo(first);
				registry.AddAlias(second, first);
			}
			else if (current_keyword == "struct")
			{
				registry.AddBlankStructType(first);
			}
			current_keyword.clear();
		}
	}
	return std::vector<int>();
}