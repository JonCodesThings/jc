#include <include/AST/Statement/ASTEnumDefinition.hpp>

#include <set>

ASTEnumDefinition::ASTEnumDefinition(ASTIdentifier &identifier, ASTEnumParts &parts) : identifier(&identifier), parts(&parts), ASTStatement(ENUM_DEFINITION) {}

llvm::Value * ASTEnumDefinition::EmitIR(IREmitter::EmitterState & state)
{
	std::vector<std::pair<std::string, int>> vals;

	int v = 0;
	for (auto &part : parts->parts)
	{
		for (auto val : vals)
		{
			if (val.second == v)
				v++;
		}
		if (part->val != nullptr)
			vals.push_back(std::make_pair(part->id->identifier, part->val->constant));
		else
			vals.push_back(std::make_pair(part->id->identifier, v));
	}

	state.typeRegistry.SetEnumValues(identifier->identifier, vals);

	return (llvm::Value*)state.typeRegistry.GetType(identifier->identifier);
}

const std::string * ASTEnumDefinition::GetType(IREmitter::EmitterState & state)
{
	return nullptr;
}
