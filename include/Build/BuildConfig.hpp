#ifndef JC_BUILDCONFIG_H
#define JC_BUILDCONFIG_H

#include <vector>
#include <string>

class BuildConfig
{
public:
	void AddModuleIncludeDirectory(const std::string &path);
	void AddModuleLibraryDirectory(const std::string &path);
	const std::vector<std::string> &GetIncludeDirs() const;
	const std::vector<std::string> &GetLibraryDirs() const;
private:
	std::vector<std::string> include_dirs;
	std::vector<std::string> lib_dirs;
};

#endif