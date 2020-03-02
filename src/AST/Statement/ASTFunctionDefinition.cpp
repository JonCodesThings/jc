#include <include/AST/Statement/ASTFunctionDefinition.hpp>

ASTFunctionDefinition::ASTFunctionDefinition(ASTIdentifier &id, ASTIdentifier &ret_type, ASTFunctionArgs &args, ASTBlock &block) : 
    declaration(new ASTFunctionDeclaration(id, ret_type, args)), block(&block), ASTStatement(FUNCTION_DEFINITION) {}

llvm::Value *ASTFunctionDefinition::EmitIR(IREmitter::EmitterState &state)
{
    auto func = declaration->EmitIR(state);

    state.frontmost = state.frontmost->CreateChildTable(declaration->identifier->identifier);

    current_function = (llvm::Function*)func;

    for (auto &arg : declaration->arguments->args)
    {
        Symbol s;
        s.identifier = arg->name->identifier;
        s.type = arg->type->identifier;
        s.classification = Symbol::Classification::VARIABLE;
        s.alloc_inst = NULL;
        state.frontmost->AddSymbol(s);
    }

    if (!block->EmitIR(state, *declaration->arguments))
        return NULL;

    return func;
}