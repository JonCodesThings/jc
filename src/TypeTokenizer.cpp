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
			continue;

		accum.push_back(ch);

		if (accum == "typedef" || accum == "struct" || accum == "alias")
		{
			current_keyword = accum;
			accum.clear();
		}
		else if (accum == ";")
		{
			accum.erase(accum.end());
			std::string first = accum.substr(0, accum.find(" "));
			std::string second = accum.substr(accum.find(" "), accum.size() - 1);
			if (accum == "typedef")
			{
				const JCType *t = registry.GetTypeInfo(first);
				registry.AddType(accum, *t->llvm_type, t->classification);
			}
			else if (accum == "alias")
			{
				const JCType *t = registry.GetTypeInfo(first);
				registry.AddAlias(second, first);
			}
			else if (accum == "struct")
			{
				registry.AddBlankStructType(first);
			}
		}
	}
	return std::vector<int>();
}