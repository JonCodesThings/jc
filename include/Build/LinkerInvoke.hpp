#ifndef JC_LINKERINVOKE_H
#define JC_LINKERINVOKE_H

#include <string>
#include <vector>

#include <include/Build/BuildConfig.hpp>

class LinkerInvoke
{
public:
	enum NATIVE_LINKER
	{
		MSVC_LINK_EXE,
		GCC_LD,
		CLANG_LINKER,
		NATIVE_LINKER_COUNT
	};

	LinkerInvoke(const NATIVE_LINKER &linker, BuildConfig &config);
	~LinkerInvoke();

	void AddObjectFile(const std::string &object_filename);
	void AddLibraryToLink(const std::string &library_to_link);

	void Invoke(const std::string &output_name);

private:
	std::vector<std::string> object_files;
	std::vector<std::string> libnames;

	NATIVE_LINKER l;
	BuildConfig &config;
};

#endif