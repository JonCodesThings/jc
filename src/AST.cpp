#include <include/AST.hpp>

void *ASTReturnStatement::EmitIR(IREmitter::EmitterState &state)
{
    switch (type)
    {
        default:
            return NULL;
        case CONSTANT:
        {
            return state.builder.CreateRet((llvm::Value*)constant.EmitIR(state));
        }
        case ID:
        {
            Symbol *symbol = state.symbolTable.GetSymbolByIdentifier(id.identifier);
            llvm::Value *retval = state.builder.CreateLoad(symbol->alloc_inst, "retval");
            return state.builder.CreateRet(retval);
        }
    }
    return NULL;
}

void *ASTIdentifier::EmitIR(IREmitter::EmitterState &state)
{
    const Symbol * s = state.symbolTable.GetSymbolByIdentifier(identifier);
    if (s)
        return s->alloc_inst;
    return NULL;
}

void *ASTUnaryOperator::EmitIR(IREmitter::EmitterState &state)
{
    const std::string &type = operatee.GetType(state);
    const Symbol *s = operatee.GetSymbol(state);

    switch (op)
    {
        default:
            return NULL;
        case INCREMENT:
        {
            if (type == "i8")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 8), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if (type == "i16")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 16), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if (type == "i32")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateAdd(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 32), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
        }
        case DECREMENT:
        {
            if (type == "i8")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 8), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if (type == "i16")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 16), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
            if (type == "i32")
            {
                llvm::Value *temp = state.builder.CreateLoad(s->alloc_inst, "temp");
                llvm::Value *added = state.builder.CreateSub(temp, llvm::ConstantInt::get(llvm::IntegerType::get(state.context, 32), 1));
                return state.builder.CreateStore(added, s->alloc_inst);
            }
        }
    }
    
    return NULL;
}

void *ASTBinaryOperator::EmitIR(IREmitter::EmitterState &state)
{
    const std::string &ltype = left.GetType(state);
    const std::string &rtype = right.GetType(state);

    llvm::Value *l_inst = (llvm::Value*)left.EmitIR(state);
    llvm::Value *r_inst = (llvm::Value*)right.EmitIR(state);

    switch (op)
    {
        case ADD:
        {
            llvm::Value *templ = state.builder.CreateLoad(l_inst, "templ");
            llvm::Value *tempr = state.builder.CreateLoad(r_inst, "tempr");
            return state.builder.CreateAdd(templ, tempr);
        }
    }
    return NULL;
}

void * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    Symbol symbol;
    symbol.classification = Symbol::VARIABLE;
    symbol.type = type.identifier;
    symbol.identifier = id.identifier;
    symbol.alloc_inst = state.builder.CreateAlloca(state.typeRegistry.GetType(type.identifier), NULL, id.identifier);
    state.symbolTable.AddSymbol(symbol);

    return symbol.alloc_inst;
}

void *ASTVariableAssignment::EmitIR(IREmitter::EmitterState &state)
{
    Symbol *symbol = state.symbolTable.GetSymbolByIdentifier(id.identifier);

    return state.builder.CreateStore((llvm::Value*)constant.EmitIR(state), symbol->alloc_inst);
}

void *ASTBlock::EmitIR(IREmitter::EmitterState &state)
{
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "temp", NULL);
    for (ASTStatement *statement : block)
        statement->EmitIR(state);
    return llvmBlock;
}

void *ASTBlock::EmitIR(IREmitter::EmitterState &state, llvm::Function &func)
{        
    auto llvmBlock = llvm::BasicBlock::Create(state.context, "entry", &func);
 
    state.builder.SetInsertPoint(llvmBlock);
    for (ASTStatement *statement : block)
        statement->EmitIR(state);
    return llvmBlock;
}

void *ASTFunctionDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    return_type.EmitIR(state);
    identifier.EmitIR(state);

    std::vector<llvm::Type*> argTypeVector;
    auto funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(state.context), argTypeVector, false);

    auto Func = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, identifier.identifier, state.module);
    return Func;
}

void *ASTFunctionDefinition::EmitIR(IREmitter::EmitterState &state)
{
    auto func = declaration.EmitIR(state);
    block.EmitIR(state, *(llvm::Function*)func);
    return func;
}