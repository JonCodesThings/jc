#include <include/AST/Statement/ASTFunctionDeclaration.hpp>

ASTFunctionDeclaration::ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args) : 
    identifier(&id), return_type(&ret_type), arguments(&args), ASTStatement(FUNCTION_DECLARATION) {}


llvm::Value *ASTFunctionDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    return_type->EmitIR(state);
    identifier->EmitIR(state);

    std::vector<llvm::Type*> argTypeVector;

    bool variadic = false;

    for (auto &arg : arguments->args)
    {
        if (arg->variadic_arg)
        {
            variadic = true;
            continue;
        }

        llvm::Type *t = state.typeRegistry.GetType(arg->type->identifier);

        if (!t)
            t = state.typeRegistry.UnwindPointerType(arg->type->identifier);

        //printf("%s, %p\n", arg->type->identifier.c_str(), t);
        if (!t)
            return NULL;

        argTypeVector.push_back(t);
    }

    auto funcType = llvm::FunctionType::get(state.typeRegistry.GetType(return_type->identifier), argTypeVector, variadic);

	llvm::GlobalValue::LinkageTypes l = llvm::GlobalValue::ExternalLinkage;
	if (exporting)
		l = llvm::GlobalValue::ExternalLinkage;


    auto Func = llvm::Function::Create(funcType, l, identifier->identifier, state.module);

    Symbol s;
    s.identifier = identifier->identifier;
    s.type = return_type->identifier;
    s.classification = Symbol::Classification::FUNCTION;
	s.function = Func;
	s.exported = exporting;

    state.symbolStack.AddSymbol(s);

    unsigned int arg_name_index = 0;
    for (auto & arg : Func->args())
        arg.setName(arguments->args[arg_name_index++]->name->identifier);

    return Func;
}

void ASTFunctionDeclaration::SetExporting(const bool exp)
{
	exporting = exp;
}