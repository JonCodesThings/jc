#include <include/LinkerInvoke.hpp>

#include <stdlib.h>

LinkerInvoke::LinkerInvoke(const NATIVE_LINKER &l) : l(l) {}

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

	switch (l)
	{
	default:
		break;
	case MSVC_LINK_EXE:
	{
		final_command.append("link.exe");
		
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
		final_command.append(" libcmt.lib");
		//printf("%s\n", final_command.c_str());
	}
		break;
	case CLANG_LINKER:
		final_command.append("clang");
		break;
	}

	system(final_command.c_str());
}