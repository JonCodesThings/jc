#include <include/ModuleRegistry.hpp>

ModuleRegistry::ModuleRegistry() {}

ModuleRegistry::~ModuleRegistry() {}

void ModuleRegistry::AddModule(const std::string &id, Module &module)
{
	if (GetModule(id))
		return;

	registry.push_back(std::make_pair(id, std::unique_ptr<Module>(std::move(&module))));
}

const Module *ModuleRegistry::GetModule(const std::string &module_name)
{
	for (auto &m : registry)
	{
		if (m.first == module_name)
			return m.second.get();
	}
	return NULL;
}

bool ModuleRegistry::EmitIRAll()
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

				}
			}
		}
	}

	return true;
}