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
	return NULL;
}

bool ModuleRegistry::EmitIRAll(llvm::LLVMContext &context, TypeRegistry &t_registry)
{
	bool all_compiled = false;

	while (!all_compiled)
	{
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
		for (auto &m : registry)
		{
			for (auto it = m.second->GetModuleDependencies().begin(); it != m.second->GetModuleDependencies().end(); it++)
			{
				for (auto &d : registry)
				{
					if (d.first == (*it))
					{
						if (!d.second->IREmitted())
						{
							if (!d.second->EmitIR(context, t_registry))
								return false;
						}
					}
				}
			}
		}

		all_compiled = true;

		for (auto &m : registry)
		{
			if (!m.second->IREmitted())
			{
				all_compiled = false;
			}
		}
	}
	return true;
}