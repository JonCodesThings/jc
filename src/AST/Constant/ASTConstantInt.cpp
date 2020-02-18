#include <include/AST/Constant/ASTConstantInt.hpp>

ASTConstantInt::ASTConstantInt(int constant) : constant(constant) {}

llvm::Value *ASTConstantInt::EmitIR(IREmitter::EmitterState &state) 
{ 
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(state.context), constant); 
}

const std::string *ASTConstantInt::GetType(IREmitter::EmitterState &state)
{
    return state.typeRegistry.GetLifetimeTypeString("i32");
}