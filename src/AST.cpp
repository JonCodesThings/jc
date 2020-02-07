#include <include/AST.hpp>

void *ASTReturnStatement::EmitIR(llvm::IRBuilder<> &builder, llvm::LLVMContext &context, llvm::Module &module)
{
    return builder.CreateRet((llvm::Value*)constant.EmitIR(builder, context, module));
}

void *ASTIdentifier::EmitIR(llvm::IRBuilder<> &builder, llvm::LLVMContext &context, llvm::Module &module)
{
    return NULL;
}

void *ASTBlock::EmitIR(llvm::IRBuilder<> &builder, llvm::LLVMContext &context, llvm::Module &module)
{
    auto llvmBlock = llvm::BasicBlock::Create(context, "temp", NULL);
    for (ASTStatement *statement : block)
        statement->EmitIR(builder, context, module);
    return llvmBlock;
}

void *ASTBlock::EmitIR(llvm::IRBuilder<> &builder, llvm::LLVMContext &context, llvm::Module &module, llvm::Function &func)
{        
    auto llvmBlock = llvm::BasicBlock::Create(context, "entry", &func);
 
    builder.SetInsertPoint(llvmBlock);
    for (ASTStatement *statement : block)
        statement->EmitIR(builder, context, module);
    return llvmBlock;
}

void *ASTFunctionDeclaration::EmitIR(llvm::IRBuilder<> &builder, llvm::LLVMContext &context, llvm::Module &module)
{
    return_type.EmitIR(builder, context, module);
    identifier.EmitIR(builder, context, module);

    std::vector<llvm::Type*> argTypeVector;
    auto funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), argTypeVector, false);

    auto Func = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, identifier.identifier, module);
    return Func;
}

void *ASTFunctionDefinition::EmitIR(llvm::IRBuilder<> &builder, llvm::LLVMContext &context, llvm::Module &module)
{
    auto func = declaration.EmitIR(builder, context, module);
    block.EmitIR(builder, context, module, *(llvm::Function*)func);
    return func;
}