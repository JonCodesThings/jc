#include <include/AST/Statement/ASTStructDefinition.hpp>

ASTStructDefinition::ASTStructDefinition(ASTIdentifier &id, ASTFunctionArgs &contains) : id(&id), contains(&contains), ASTStatement(STRUCT_DEFINITION) {}

llvm::Value *ASTStructDefinition::EmitIR(IREmitter::EmitterState &state)
{
    std::vector<llvm::Type *> members;

    for (auto &member : contains->args)
    {
        llvm::Type *t = state.typeRegistry.GetType(member->type->identifier);

        if (!t)
            t = state.typeRegistry.UnwindPointerType(member->type->identifier);

        if (!t)
            return NULL;

        members.push_back(t);
    }

    state.typeRegistry.SetStructType(id->identifier , members);

    return (llvm::Value*)state.typeRegistry.GetType(id->identifier);
}