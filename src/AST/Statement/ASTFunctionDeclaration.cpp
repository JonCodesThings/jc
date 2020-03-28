#include <include/AST/Statement/ASTFunctionDeclaration.hpp>

ASTFunctionDeclaration::ASTFunctionDeclaration(ASTIdentifier &ret_type, ASTIdentifier &id, ASTFunctionArgs &args) : 
    identifier(&id), return_type(&ret_type), arguments(&args), ASTStatement(FUNCTION_DECLARATION) {}


llvm::Value *ASTFunctionDeclaration::EmitIR(IREmitter::EmitterState &state)
{
	//emit IR for both the return type and identifier
    return_type->EmitIR(state);
    identifier->EmitIR(state);

	//vector to store the llvm types of the function arguments
    std::vector<llvm::Type*> argTypeVector;

    bool variadic = false;

    for (auto &arg : arguments->args)
    {
		//if the arg indicates variadic skip the rest of this iteration
        if (arg->variadic_arg)
        {
            variadic = true;
            continue;
        }

		//get the type from the registry
        llvm::Type *t = state.typeRegistry.GetType(arg->type->identifier);

		//failing that unwind the pointer type
        if (!t)
            t = state.typeRegistry.UnwindPointerType(arg->type->identifier);

		//failing that give up
        if (!t)
            return nullptr;

		//add it to the vector
        argTypeVector.push_back(t);
    }

	//get the llvm type of the function
    llvm::FunctionType *func_type = llvm::FunctionType::get(state.typeRegistry.GetType(return_type->identifier), argTypeVector, variadic);

	//set up the linkage
	//TODO: fix this so we don't have external linkage on every function
	llvm::GlobalValue::LinkageTypes l = llvm::GlobalValue::ExternalLinkage;
	if (exporting)
		l = llvm::GlobalValue::ExternalLinkage;

	//get the function from llvm
    llvm::Function *func = llvm::Function::Create(func_type, l, identifier->identifier, state.module);

	//set up the symbol for the function
    Symbol s;
	if (current_function)
	{
		if (identifier->identifier.find(std::string(current_function->getName()) + "__") != std::string::npos)
			s.identifier = identifier->identifier.substr(identifier->identifier.find_last_of('_') + 1, identifier->identifier.length() - identifier->identifier.find_last_of('_') + 1);
	}
	else
		s.identifier = identifier->identifier;
    s.type = return_type->identifier;
    s.classification = Symbol::Classification::FUNCTION;
	s.function = func;
	s.exported = exporting;

	//add it to the symbol stack
    state.symbolStack.AddSymbol(s);

	//also set up the way of referencing arguments by identifier
    unsigned int arg_name_index = 0;
    for (auto & arg : func->args())
        arg.setName(arguments->args[arg_name_index++]->name->identifier);

    return func;
}

void ASTFunctionDeclaration::SetExporting(const bool exp)
{
	exporting = exp;
}