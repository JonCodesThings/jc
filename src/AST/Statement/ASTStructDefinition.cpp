#include <include/AST/Statement/ASTStructDefinition.hpp>

ASTStructDefinition::ASTStructDefinition(ASTIdentifier &id, ASTFunctionArgs &contains) : id(&id), contains(&contains), ASTStatement(STRUCT_DEFINITION) {}

llvm::Value *ASTStructDefinition::EmitIR(IREmitter::EmitterState &state)
{
	//store the different member types in this
    std::vector<llvm::Type *> members;

	//store the different member names and typenames in these
    std::vector<std::string> member_names;
    std::vector<std::string> member_typenames;

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
            return NULL;

		//push back the relevant data into the right vectors
        members.push_back(t);
        member_names.push_back(member->name->identifier);
        member_typenames.push_back(member->type->identifier);
    }

	//set the struct type
    state.typeRegistry.SetStructType(id->identifier, members, member_names, member_typenames);

	//return the type
    return (llvm::Value*)state.typeRegistry.GetType(id->identifier);
}