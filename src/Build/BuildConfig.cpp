#include <include/Build/BuildConfig.hpp>

void BuildConfig::AddModuleIncludeDirectory(const std::string &path)
{
	include_dirs.push_back(path);
}

void BuildConfig::AddModuleLibraryDirectory(const std::string &path)
{
	lib_dirs.push_back(path);
}

void BuildConfig::AddLibraryLink(const std::string & lib)
{
	libs.push_back(lib);
}

const std::vector<std::string> &BuildConfig::GetIncludeDirs() const
{
	return include_dirs;
}
const std::vector<std::string> &BuildConfig::GetLibraryDirs() const
{
	return lib_dirs;
}

const std::vector<std::string>& BuildConfig::GetLibraries() const
{
	return libs;
}
