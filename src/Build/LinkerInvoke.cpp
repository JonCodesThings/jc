#include <include/Build/LinkerInvoke.hpp>

#include <stdlib.h>

LinkerInvoke::LinkerInvoke(const NATIVE_LINKER &l, BuildConfig &config) : l(l), config(config) {}

LinkerInvoke::~LinkerInvoke() {}

void LinkerInvoke::AddLibraryToLink(const std::string &lib)
{
	for (auto l : libnames)
	{
		if (l == lib)
			return;
	}

	libnames.push_back(lib);
}

void LinkerInvoke::AddObjectFile(const std::string &object_filename)
{
	for (auto l : object_files)
	{
		if (l == object_filename)
			return;
	}

	object_files.push_back(object_filename);
}

void LinkerInvoke::Invoke(const std::string &output_name)
{
	std::string final_command;

	//depending on what platform we're on and what linker is available we'll do different things
	switch (l)
	{
	default:
		break;
	//THIS ONLY WORKS IN THE DEVELOPER PROMT CURRENTLY
	//set up the MSVC linker with args
	case MSVC_LINK_EXE:
	{
		//std::string vcvars = "\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\"";
		//printf("%s\n", vcvars.c_str());
		//std::system(vcvars.c_str());

		final_command.append("link");
		
		for (auto o : object_files)
			final_command.append(" " + o + ".o ");

		final_command.append("/OUT:" + output_name + ".exe /NOLOGO");

		//system("\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat\"");
		//system("echo %path%");
		//final_command.append(" /LIBPATH:\"C:\\Program Files(x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\ucrt\\x64\" ");
		/*final_command.append(" /LIBPATH:\"C:\\Program Files(x86)\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64\" ");*/
		//final_command.append(" /LIBPATH:\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\lib\\x64\"");
		/*final_command.append(" /LIBPATH:\"C:\\Program Files(x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Tools\\MSVC\\14.16.27023\\atlmfc\\lib\\x64\"");
		final_command.append(" /LIBPATH:\"C:\\Program Files(x86)\\Microsoft Visual Studio\\2017\\Community\\VC\\Auxiliary\\VS\\lib\\x64\"");*/
		final_command.append(" libcmt.lib ");

		auto libs = config.GetLibraries();

		for (auto lib : libs)
			final_command.append(lib + " ");
		//printf("%s\n", final_command.c_str());
	}
		break;
	//TODO: Jon
	//properly set up the CLANG linker stuff
	case CLANG_LINKER:
		final_command.append("clang");

		for (auto o : object_files)
			final_command.append(" " + o + ".o ");

		final_command.append("-o");

		final_command.append(output_name + ".out");
		break;
	}

	//invoke the linker
	system(final_command.c_str());
}