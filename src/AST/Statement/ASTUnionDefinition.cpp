#include <include/AST/Statement/ASTUnionDefinition.hpp>

ASTUnionDefinition::ASTUnionDefinition(ASTIdentifier &id, ASTStructMemberDeclarations &contains) : id(&id), contains(&contains), ASTStatement(UNION_DEFINITION) {}

llvm::Value * ASTUnionDefinition::EmitIR(IREmitter::EmitterState & state)
{
	//store the different member types in this
	std::vector<llvm::Type *> members;

	//store the different member names and typenames in these
	std::vector<std::string> member_names;
	std::vector<std::string> member_typenames;

	llvm::Type *largest = nullptr;

	llvm::DataLayout dl(state.module);
	std::string largest_typename;

	//for each member
	for (auto &member : contains->args)
	{
		//get the type
		llvm::Type *t = state.typeRegistry.GetType(member->type->identifier);

		//or unwind it
		if (!t)
			t = state.typeRegistry.UnwindPointerType(member->type->identifier);

		//or just give up
		if (!t)
			return nullptr;

		if (!largest)
		{
			largest = t;
			largest_typename = member->type->identifier;
		}


		if (dl.getTypeSizeInBits(largest) <= dl.getTypeSizeInBits(t))
		{
			largest = t;
			largest_typename = member->type->identifier;
		}

		//push back the relevant data into the right vectors
		members.push_back(t);
		member_names.push_back(member->name->identifier);
		member_typenames.push_back(member->type->identifier);
	}

	state.typeRegistry.SetUnionType(id->identifier, member_names, member_typenames, largest_typename, state.module_name, exporting);

	//return the type
	return (llvm::Value*)state.typeRegistry.GetType(id->identifier);
}
