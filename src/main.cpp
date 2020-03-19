#define YY_NO_UNISTD_H 1

#include <include/AST.hpp>
#include <gen/jc_lex.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>
#include <include/LinkerInvoke.hpp>
#include <include/ModuleRegistry.hpp>
#include <include/ModuleTokenizer.hpp>
#include <include/ModuleParser.hpp>
#include <include/ObjectFileEmitter.hpp>
#include <include/TypeTokenizer.hpp>
#include <include/TypeParser.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

#include <fstream>

extern std::unique_ptr<ASTBlock> base;
extern FILE *yyin;
extern const char *yycurrentfilename;
extern int yyparse();
extern TypeRegistry *registry;


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

	//TODO: actually detect what linker we're using
	LinkerInvoke invoke(LinkerInvoke::MSVC_LINK_EXE);

    registry->SetupBuiltinJCTypes();

	std::vector<std::pair<std::string, bool>> modules_to_build;

	std::string initial = args[1];
	initial = initial.substr(initial.find('\\') + 1, initial.find('.'));

	modules_to_build.push_back(std::make_pair(args[1], false));

	bool found_all_modules = false;
	int prev_module_count = 1;
	do
	{
		for (int i = 0; i < modules_to_build.size(); i++)
		{
			if (modules_to_build[i].second)
				continue;

			std::ifstream m_in(modules_to_build[i].first);
			std::string m_string((std::istreambuf_iterator<char>(m_in)), std::istreambuf_iterator<char>());
			m_in.close();

			std::vector<Token> type_tokens = type_tokenizer.Tokenize(m_string);
			type_parser.Parse(type_tokens);

			std::vector<Token> module_tokens = module_tokenizer.Tokenize(m_string);

			YY_BUFFER_STATE s = yy_scan_string(m_string.c_str());

			int p = yyparse();
			yy_delete_buffer(s);

			std::vector<std::string> module_depends;

			for (auto imp : module_tokens)
			{
				if (imp.token_type == ModuleTokenizer::IDENTIFIER_T)
				{
					auto not_built = std::find(modules_to_build.begin(), modules_to_build.end(), std::make_pair(*imp.string, false));
					auto built = std::find(modules_to_build.begin(), modules_to_build.end(), std::make_pair(*imp.string, true));

					if (not_built == modules_to_build.end() && built == modules_to_build.end())
						modules_to_build.push_back(std::make_pair(*imp.string, false));

					module_depends.push_back(*imp.string);

					delete imp.string;
				}
			}
			module_tokens.clear();

			Module *module = new Module(modules_to_build[i].first, *base.release(), module_depends);
			module_registry.AddModule(modules_to_build[i].first, *module);
			modules_to_build[i].second = true;
		}
		if (modules_to_build.size() == prev_module_count)
		{
			found_all_modules = true;
			break;
		}
		prev_module_count = modules_to_build.size();
	} while (!found_all_modules);

	if (!module_registry.EmitIRAll(context, *registry))
	{
		printf("Compilation failed. Please fix errors!\n");
		return 0;
	}

	for (auto m : modules_to_build)
	{
		object_file_emitter.EmitObjectFile(*module_registry.GetModule(m.first)->GetLLVMModule());

		invoke.AddObjectFile(m.first);
	}

	printf("Invoking linker...\n");
	//invoke.Invoke(modules_to_build[0].first.substr(0, modules_to_build[0].first.find('.')));
	invoke.Invoke(modules_to_build[0].first);

	printf("Compilation and linking complete!\n");

    return 0;
}
