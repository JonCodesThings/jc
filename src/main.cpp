#define YY_NO_UNISTD_H 1

#include <include/AST.hpp>
#include <gen/jc_lex.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>
#include <include/Build/LinkerInvoke.hpp>
#include <include/ModuleRegistry.hpp>
#include <include/Tokenizers/ModuleTokenizer.hpp>
#include <include/Parsers/ModuleParser.hpp>
#include <include/Build/ObjectFileEmitter.hpp>
#include <include/Tokenizers/TypeTokenizer.hpp>
#include <include/Parsers/TypeParser.hpp>
#include <include/Build/BuildConfig.hpp>
#include <include/Tokenizers/BuildTokenizer.hpp>
#include <include/Parsers/BuildParser.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

#include <fstream>

extern std::unique_ptr<ASTBlock> base;
extern FILE *yyin;
extern const char *yycurrentfilename;
extern int yyparse();
extern TypeRegistry *registry;

struct ModuleData
{
	std::string name;
	std::string raw_contents;
	bool prescanned = false;
	std::vector<std::string> module_depends;
};


int main(int argc, const char **args)
{
    llvm::LLVMContext context;
    registry = new TypeRegistry(context);

	TypeTokenizer type_tokenizer;
	TypeParser type_parser(*registry);

	ModuleTokenizer module_tokenizer;

	ModuleRegistry module_registry;

	ObjectFileEmitter object_file_emitter(context);
	object_file_emitter.Initialize();

	BuildConfig config;
	BuildTokenizer build_tokenizer;
	BuildParser build_parser(config);

	//TODO: actually detect what linker we're using
	LinkerInvoke invoke(LinkerInvoke::MSVC_LINK_EXE, config);

    registry->SetupBuiltinJCTypes();

	std::vector<ModuleData> modules_to_build;

	std::string initial = args[1];
	initial = initial.substr(initial.find('\\') + 1, initial.find('.'));

	ModuleData d;
	d.name = args[1];
	d.prescanned = false;

	modules_to_build.push_back(d);

	bool found_all_modules = false;
	int prev_module_count = 1;

	config.AddModuleIncludeDirectory("stdlib");

	do
	{
		for (int i = 0; i < modules_to_build.size(); i++)
		{
			if (modules_to_build[i].prescanned)
				continue;

			auto include = config.GetIncludeDirs();

			std::ifstream m_in(modules_to_build[i].name);

			bool open = m_in.is_open();

			if (!open)
			{
				for (auto it = include.begin(); it != include.end(); it++)
				{
					m_in = std::ifstream((*it) + "/" + modules_to_build[i].name);
					open = m_in.is_open();

					if (open)
						break;
				}
			}

			std::string m_string((std::istreambuf_iterator<char>(m_in)), std::istreambuf_iterator<char>());
			m_in.close();

			modules_to_build[i].raw_contents = m_string;

			std::vector<Token> build_tokens = build_tokenizer.Tokenize(m_string);
			build_parser.Parse(build_tokens);

			std::vector<Token> type_tokens = type_tokenizer.Tokenize(m_string);
			type_parser.Parse(type_tokens);

			std::vector<Token> module_tokens = module_tokenizer.Tokenize(m_string);

			std::vector<std::string> module_depends;

			for (auto imp : module_tokens)
			{
				if (imp.token_type == ModuleTokenizer::IDENTIFIER_T)
				{
					bool found = false;
					for (auto m : modules_to_build)
					{
						if (m.name == *imp.string)
						{
							found = true;
							break;
						}
					}

					if (!found)
					{
						ModuleData d;
						d.name = *imp.string;
						d.prescanned = false;
						modules_to_build.push_back(d);
					}

					module_depends.push_back(*imp.string);

					delete imp.string;
				}
			}
			module_tokens.clear();

			modules_to_build[i].module_depends = module_depends;
		}
		if (modules_to_build.size() == prev_module_count)
		{
			found_all_modules = true;
			break;
		}
		prev_module_count = modules_to_build.size();
	} while (!found_all_modules);

	for (auto m : modules_to_build)
	{

		yycurrentfilename = m.name.c_str();
		YY_BUFFER_STATE s = yy_scan_string(m.raw_contents.c_str());
		yylineno = 1;

		int p = yyparse();
		yy_delete_buffer(s);

		Module *module = new Module(m.name, *base.release(), m.module_depends);
		module_registry.AddModule(m.name, *module);
	}

	if (!module_registry.EmitIRAll(context, *registry))
	{
		printf("Compilation failed. Please fix errors!\n");
		return 0;
	}



	for (auto m : modules_to_build)
	{
		object_file_emitter.EmitObjectFile(*module_registry.GetModule(m.name)->GetLLVMModule());

		invoke.AddObjectFile(m.name);
	}

	printf("Invoking linker...\n");
	invoke.Invoke(modules_to_build[0].name);

	printf("Compilation and linking complete!\n");

    return 0;
}
