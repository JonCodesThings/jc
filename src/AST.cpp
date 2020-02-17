#include <include/AST.hpp>

extern const char *yycurrentfilename;

llvm::Value *ASTReturnStatement::EmitIR(IREmitter::EmitterState &state)
{
    switch (type)
    {
        default:
            return NULL;
        case CONSTANT:
        {
            return state.builder.CreateRet(constant.EmitIR(state));
        }
        case ID:
        {
            Symbol *symbol = state.frontmost->GetSymbolByIdentifier(id.identifier);
            llvm::Value *retval = state.builder.CreateLoad(symbol->alloc_inst, "retval");
            return state.builder.CreateRet(retval);
        }
    }
    return NULL;
}

llvm::Value *ASTIdentifier::EmitIR(IREmitter::EmitterState &state)
{
    const Symbol * s = state.frontmost->GetSymbolByIdentifier(identifier);
    if (s)
        return s->alloc_inst;
    return NULL;
}

llvm::Value *ASTUnaryOperator::EmitIR(IREmitter::EmitterState &state)
{
    const std::string *type = operatee.GetType(state);
    const Symbol *s = operatee.GetSymbol(state);

    switch (op)
    {
        default:
            return NULL;
        case ADDRESS_OF:
        {
            return s->alloc_inst;
        }
        case DEREFERENCE:
        {
            llvm::Value *v = state.builder.CreateLoad(s->alloc_inst, "temp_deref");
            return state.builder.CreateLoad(v);
        }
        case CAST:
        {
            const std::string *cast_to = cast->GetType(state);

            if (state.typeRegistry.IsTypeNumeric(*type) && state.typeRegistry.IsTypeNumeric(*cast_to))
            {
                llvm::Type *conver = state.typeRegistry.GetNarrowingConversion(*type, *cast_to);

                if (!conver)
                    conver = state.typeRegistry.GetWideningConversion(*type, *cast_to);

                if (!conver)
                    return NULL;

                llvm::Value *v = operatee.EmitIR(state);

                if (s)
                    v = state.builder.CreateLoad(s->alloc_inst, "temp");


                //TODO: allow this to support unsigned types

                JCType::TYPE_CLASSIFICATION t = state.typeRegistry.GetTypeInfo(*cast_to)->classification;
                JCType::TYPE_CLASSIFICATION f = state.typeRegistry.GetTypeInfo(*type)->classification;

                if (f == JCType::TYPE_CLASSIFICATION::FLOAT && t == JCType::TYPE_CLASSIFICATION::FLOAT)
                    return state.builder.CreateFPCast(v, conver);
                if (f == JCType::TYPE_CLASSIFICATION::INT && t == JCType::TYPE_CLASSIFICATION::INT)
                    return state.builder.CreateIntCast(v, conver, true);
                if (f == JCType::TYPE_CLASSIFICATION::FLOAT && t == JCType::TYPE_CLASSIFICATION::INT)
                    return state.builder.CreateFPToSI(v, conver);
                if (f == JCType::TYPE_CLASSIFICATION::INT && t == JCType::TYPE_CLASSIFICATION::FLOAT)
                    return state.builder.CreateSIToFP(v, conver);
                return NULL;
            }

        }
        case INCREMENT:
        {
            if ((*type) == "i8")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 8), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if ((*type) == "i16")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 16), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if ((*type) == "i32")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 32), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
        }
        case DECREMENT:
        {
            if ((*type) == "i8")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 8), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if ((*type) == "i16")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 16), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if ((*type) == "i32")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 32), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
        }
    }
    
    return NULL;
}

llvm::Value *ASTBinaryOperator::EmitIR(IREmitter::EmitterState &state)
{
    const std::string *ltype = left.GetType(state);
    const std::string *rtype = right.GetType(state);

    printf("ltype: %p  rtype: %p\n", ltype, rtype);

    llvm::Value *l_inst = left.EmitIR(state);
    llvm::Value *r_inst = right.EmitIR(state);

    printf("l_inst: %p  r_inst: %p\n", l_inst, r_inst);

    const Symbol *l_symbol = left.GetSymbol(state);
    const Symbol *r_symbol = right.GetSymbol(state);

    printf("l_symbol: %p  r_symbol: %p\n", l_symbol, r_symbol);

    llvm::Value *templ;
    llvm::Value *tempr;

    if (l_symbol)
        templ = state.builder.CreateLoad(l_inst, "templ");
    else
        templ = l_inst;

    if (r_symbol)
        tempr = state.builder.CreateLoad(r_inst, "tempr");
    else
        tempr = r_inst;


    switch (op)
    {
        case ADD:
        {
            return state.builder.CreateAdd(templ, tempr);
        }
        case SUBTRACT:
        {
            return state.builder.CreateSub(templ, tempr);
        }
    }
    return NULL;
}

llvm::Value * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.identifier = id.identifier;

    auto temp = (ASTConstantInt*)array_size;

    if (array_size)
    {
        symbol.alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetArrayType(type.identifier, temp->constant), NULL, id.identifier);
    }
    else
    {
        symbol.alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(type.identifier), NULL, id.identifier);
        symbol.type = type.identifier;
    }

    if (node)
    {
        llvm::Value *v = node->EmitIR(state);
        state.builder.CreateStore(v, symbol.alloc_inst);
    }

    state.frontmost->AddSymbol(symbol);

    return symbol.alloc_inst;
}

llvm::Value *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
    Symbol *symbol = state.frontmost->GetSymbolByIdentifier(id.identifier);
    const Symbol *node_symbol = node.GetSymbol(state);

    if (!symbol)
    {
        if (*node.GetType(state) != *id.GetType(state))
        {
            printf("%s:%d:%d Error: types do not match for assignment (type %s expected, type %s given)\n",
            yycurrentfilename, line_number, start_char, (*id.GetType(state)).c_str(), (*node.GetType(state)).c_str());
            return NULL;
        }
    }
    else if (symbol && node_symbol)
    {
        if (symbol->type != node_symbol->type)
        {
            printf("%s:%d:%d Error: types do not match for assignment (type %s expected, type %s given)\n",
            yycurrentfilename, line_number, start_char, symbol->type.c_str(), node_symbol->type.c_str());
            return NULL;
        }
    }

    if (node_symbol)
    {
        llvm::Value *temp = state.builder.CreateLoad(node_symbol->alloc_inst, "temp");
        return state.builder.CreateStore(temp, symbol->alloc_inst);
    }

    return state.builder.CreateStore(node.EmitIR(state), symbol->alloc_inst);
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state)
{
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "temp", NULL);
    for (ASTStatement *statement : block)
    {
        if (!statement->EmitIR(state))
            return NULL;
    }
    return llvmBlock;
}

llvm::Value *ASTBlock::EmitIR(IREmitter::EmitterState &state, ASTFunctionArgs &args, llvm::Function &func)
{        
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "entry", &func);
 
    state.builder.SetInsertPoint(llvmBlock);

    for (auto &arg : func.args())
    {
        Symbol *s = state.frontmost->GetSymbolByIdentifier(arg.getName());
        s->alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(s->type), NULL, arg.getName());
        state.builder.CreateStore(&arg, s->alloc_inst);
    }

    for (ASTStatement *statement : block)
    {
        if (!statement->EmitIR(state))
            return NULL;
    }
    return llvmBlock;
}

llvm::Value *ASTFunctionCall::EmitIR(IREmitter::EmitterState &state)
{
    auto Func = state.module.getFunction(identifier.identifier);
    
    std::vector<llvm::Value*> argvals;

    if (args)
    {
        for (auto &arg : *args)
            argvals.push_back(arg->EmitIR(state));
    }
    
    return state.builder.CreateCall(Func, argvals, identifier.identifier + "_call");
}

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

llvm::Value *ASTFunctionDefinition::EmitIR(IREmitter::EmitterState &state)
{
    auto func = declaration.EmitIR(state);

    state.frontmost = state.frontmost->CreateChildTable(declaration.identifier.identifier);

    for (auto &arg : declaration.arguments.args)
    {
        Symbol s;
        s.identifier = arg.name.identifier;
        s.type = arg.type.identifier;
        s.classification = Symbol::Classification::VARIABLE;
        s.alloc_inst = NULL;
        state.frontmost->AddSymbol(s);
    }

    if (!block.EmitIR(state, declaration.arguments, *(llvm::Function*)func))
        return NULL;

    return func;
}