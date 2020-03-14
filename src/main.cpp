#define YY_NO_UNISTD_H 1

#include <include/AST.hpp>
#include <gen/jc_lex.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>
#include <include/ModuleTokenizer.hpp>
#include <include/ModuleParser.hpp>
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

    registry->SetupBuiltinJCTypes();

	std::ifstream t_in(args[1]);
	std::string t_string((std::istreambuf_iterator<char>(t_in)), std::istreambuf_iterator<char>());
	t_in.close();
	std::vector<Token> type_tokens = type_tokenizer.Tokenize(t_string);
	type_parser.Parse(type_tokens);

	std::vector<Token> module_tokens = module_tokenizer.Tokenize(t_string);

	std::string processed_input;

	for (auto imp : module_tokens)
	{
		if (imp.token_type == ModuleTokenizer::IDENTIFIER_T)
		{
			processed_input += *imp.string;
			delete imp.string;
		}
	}

	processed_input += t_string;

	YY_BUFFER_STATE s = yy_scan_string(processed_input.c_str());

    yycurrentfilename = args[1];
    int p = yyparse();
	yy_delete_buffer(s);
    if (base)
    {
        llvm::Module module("jc alpha", context);
        IREmitter emitter(module, context, *registry);

        if (emitter.EmitIR(base.get()))
        {
            std::error_code ec;
            std::string o = args[1];
            o.append(".ir");
            llvm::raw_fd_ostream out(o, ec);
            llvm::WriteBitcodeToFile(module, out);
            out.close();
        }
        else
        {
            printf("Compilation failed. Please fix errors!\n");
        }

        
    }

    return 0;
}
