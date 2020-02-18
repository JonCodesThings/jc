#include <include/AST/Constant/ASTConstantFloat.hpp>

ASTConstantFloat::ASTConstantFloat(float constant) : constant(constant) {}

llvm::Value *ASTConstantFloat::EmitIR(IREmitter::EmitterState &state) 
{ 
    return llvm::ConstantFP::get(llvm::Type::getFloatTy(state.context), constant); 
}

const std::string *ASTConstantFloat::GetType(IREmitter::EmitterState &state)
{
    return state.typeRegistry.GetLifetimeTypeString("f32");
}