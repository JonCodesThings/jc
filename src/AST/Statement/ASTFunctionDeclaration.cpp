#include <include/AST/Statement/ASTFunctionDeclaration.hpp>

ASTFunctionDeclaration::ASTFunctionDeclaration() : 
    identifier(*new ASTIdentifier("function id: TBD")), return_type(*new ASTIdentifier("return type: TBD")), arguments(*new ASTFunctionArgs()) {}

ASTFunctionDeclaration::ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args) : 
    identifier(id), return_type(ret_type), arguments(args) {}


llvm::Value *ASTFunctionDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    return_type.EmitIR(state);
    identifier.EmitIR(state);

    std::vector<llvm::Type*> argTypeVector;

    for (auto arg : arguments.args)
        argTypeVector.push_back(state.typeRegistry.GetType(arg.type.identifier));

    auto funcType = llvm::FunctionType::get(state.typeRegistry.GetType(return_type.identifier), argTypeVector, false);

    auto Func = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, identifier.identifier, state.module);

    Symbol s;
    s.identifier = identifier.identifier;
    s.type = return_type.identifier;
    s.classification = Symbol::Classification::FUNCTION;

    state.frontmost->AddSymbol(s);

    unsigned int arg_name_index = 0;
    for (auto & arg : Func->args())
        arg.setName(arguments.args[arg_name_index++].name.identifier);

    return Func;
}