#ifndef JC_OBJECTFILEEMITTER_H
#define JC_OBJECTFILEEMITTER_H

#include "llvm/IR/Module.h"

namespace llvm
{
	class TargetMachine;
}

class ObjectFileEmitter
{
public:
	ObjectFileEmitter(llvm::LLVMContext &context);
	~ObjectFileEmitter();

	void Initialize();
	bool EmitObjectFile(llvm::Module &module);
private:
	llvm::LLVMContext &context;
	llvm::PassRegistry *pass_registry;
	llvm::TargetMachine *target_machine;
	std::string target_triple;
};

#endif