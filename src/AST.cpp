#include <include/AST.hpp>

void *ASTReturnStatement::EmitIR(IREmitter::EmitterState &state)
{
    switch (type)
    {
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
    return NULL;
}

void * ASTVariableDeclaration::EmitIR(IREmitter::EmitterState &state)
{
    Symbol symbol;
    symbol.type = Symbol::VARIABLE;
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