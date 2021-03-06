#include <include/AST/Statement/ASTFunctionDefinition.hpp>

ASTFunctionDefinition::ASTFunctionDefinition(ASTIdentifier &id, ASTIdentifier &ret_type, ASTFunctionArgs &args, ASTBlock &block) : 
    declaration(new ASTFunctionDeclaration(id, ret_type, args)), block(&block), ASTStatement(FUNCTION_DEFINITION) {}

ASTFunctionDefinition::ASTFunctionDefinition(ASTIdentifier &id, ASTFunctionArgs &args, ASTBlock &block) :
	declaration(), id(&id), args(&args), block(&block), ASTStatement(FUNCTION_DEFINITION) {}

llvm::Value *ASTFunctionDefinition::EmitIR(IREmitter::EmitterState &state)
{
	if (!declaration)
	{
		state.syntheticStack.Clear();
		state.syntheticStack = state.symbolStack;

		state.syntheticStack.Push(id->identifier);

		for (auto &arg : args->args)
		{
			Symbol s;
			s.identifier = arg->name->identifier;
			s.type = arg->type->identifier;
			s.classification = s.VARIABLE;
			state.syntheticStack.AddSymbol(s);
		}

		const std::string *typestring = block->GetType(state);
		if (!typestring)
			return nullptr;
		state.syntheticStack.Clear();
		declaration = std::make_unique<ASTFunctionDeclaration>(*new ASTIdentifier(*typestring), *id.release(), *args.release());
	}

	//get the function by emitting the declaration's IR
    llvm::Value *func = declaration->EmitIR(state);

	//push a new symbol table onto the stack
    state.symbolStack.Push(declaration->identifier->identifier);

	auto prev_curr_func = current_function;

	//downcast the current function
    current_function = (llvm::Function*)func;

	//add the args as symbols on that new symbol table
    for (auto &arg : declaration->arguments->args)
    {
        Symbol s;
        s.identifier = arg->name->identifier;
        s.type = arg->type->identifier;
        s.classification = Symbol::Classification::VARIABLE;
        s.alloc_inst = nullptr;
		s.exported = declaration->exporting;
        state.symbolStack.AddSymbol(s);
    }

	//emit the function body's IR
    if (!block->EmitIR(state, *declaration->arguments))
        return nullptr;

	//pop the symbol table
    state.symbolStack.Pop();

	current_function = prev_curr_func;

	//return the function
    return func;
}


void ASTFunctionDefinition::SetExporting(const bool expa)
{
	declaration->SetExporting(expa);
}