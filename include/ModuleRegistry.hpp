#ifndef JC_MODULEREGISTRY_H
#define JC_MODULEREGISTRY_H

#include "Module.hpp"

#include "IREmitter.hpp"

class ModuleRegistry
{
public:
	ModuleRegistry();
	~ModuleRegistry();

	void AddModule(const std::string &module_name, Module &module);

	const Module *GetModule(const std::string &module_name);

	bool EmitIRAll();
private:
	void EmitModuleIR(Module *module);

	std::vector<std::pair<std::string, std::unique_ptr<Module>>> registry;
};

#endif