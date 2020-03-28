#include <include/ModuleRegistry.hpp>

ModuleRegistry::ModuleRegistry() {}

ModuleRegistry::~ModuleRegistry() {}

void ModuleRegistry::AddModule(const std::string &id, Module &module)
{
	if (GetModule(id))
		return;

	registry.push_back(std::make_pair(id, std::unique_ptr<Module>(std::move(&module))));
}

Module *ModuleRegistry::GetModule(const std::string &module_name)
{
	for (auto &m : registry)
	{
		if (m.first == module_name)
			return m.second.get();
	}
	return nullptr;
}

bool ModuleRegistry::EmitIRAll(llvm::LLVMContext &context, TypeRegistry &t_registry)
{
	//flag for checking everything has compiled
	bool all_compiled = false;

	//emit IR for every module that has no dependencies first
	for (auto &m : registry)
	{
		if (!m.second->IREmitted())
		{
			if (m.second->GetModuleDependencies().empty())
			{
				if (!m.second->EmitIR(context, t_registry))
					return false;
			}
		}
	}

	//while that flag isn't set
	while (!all_compiled)
	{
		for (auto &m : registry)
		{
			//check if the module can be built
			bool can_module_be_built = true;
			if (m.second->IREmitted())
				continue;
			for (auto it = m.second->GetModuleDependencies().begin(); it != m.second->GetModuleDependencies().end(); it++)
			{
				//find each dependency in the registry, build it and add the dependency symbols to the module
				for (auto &d : registry)
				{
					if (d.first == (*it))
					{
						if (!d.second->IREmitted())
						{
							if (!d.second->EmitIR(context, t_registry))
								return false;
						}
						m.second->AddDependencySymbols(d.second->GetModuleSymbolTable().GetExportedSymbols());
						if (!d.second->IREmitted())
							can_module_be_built = false;
					}
				}
			}
			//if the module can be built and it hasn't been built yet do it
			if (can_module_be_built && !m.second->IREmitted())
			{
				if (!m.second->EmitIR(context, t_registry))
					return false;
			}
		}

		all_compiled = true;

		//check if everything has been built
		for (auto &m : registry)
		{
			if (!m.second->IREmitted())
				all_compiled = false;
		}
	}
	return true;
}