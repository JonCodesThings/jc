#ifndef JC_ASTFUNCPTRDEF_H
#define JC_ASTFUNCPTRDEF_H

#include <include/AST/ASTStatement.hpp>

class ASTFunctionPointerDefinition : public ASTStatement
{
public:
	ASTFunctionPointerDefinition();
	llvm::Value *EmitIR(IREmitter::EmitterState &state);
};

#endif