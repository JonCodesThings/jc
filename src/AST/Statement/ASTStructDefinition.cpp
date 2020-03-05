#include <include/AST/Statement/ASTStructDefinition.hpp>

ASTStructDefinition::ASTStructDefinition(ASTIdentifier &id, ASTFunctionArgs &contains) : id(&id), contains(&contains), ASTStatement(STRUCT_DEFINITION) {}

llvm::Value *ASTStructDefinition::EmitIR(IREmitter::EmitterState &state)
{
    std::vector<llvm::Type *> members;

    std::vector<std::string> member_names;

    for (auto &member : contains->args)
    {
        llvm::Type *t = state.typeRegistry.GetType(member->type->identifier);

        if (!t)
            t = state.typeRegistry.UnwindPointerType(member->type->identifier);

        if (!t)
            return NULL;

        members.push_back(t);
        member_names.push_back(member->name->identifier);
    }

    state.typeRegistry.SetStructType(id->identifier, members, member_names);

    return (llvm::Value*)state.typeRegistry.GetType(id->identifier);
}