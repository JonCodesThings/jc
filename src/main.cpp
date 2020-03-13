#include <include/AST.hpp>
#include <gen/jc_type_parser.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>
#include <include/TypeTokenizer.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

#include <fstream>

extern std::unique_ptr<ASTBlock> base;
extern FILE *yyin;
extern FILE *type_in;
extern const char *yycurrentfilename;
extern const char *type_currentfilename;
extern int yyparse();
extern int type_parse();
extern TypeRegistry *registry;


int main(int argc, const char **args)
{
    llvm::LLVMContext context;
    registry = new TypeRegistry(context);
	TypeTokenizer type(*registry);
    registry->SetupBuiltinJCTypes();
    //type_in = fopen(args[1], "r");
	std::ifstream t_in(args[1]);
	std::string t_string((std::istreambuf_iterator<char>(t_in)), std::istreambuf_iterator<char>());
	type.Tokenize(t_string);
    //if (!type_in)
    //{
    //    printf("Type preparser failed!\n");
    //    return 0;
    //}
    //int x = type_parse();
    //fclose(type_in);
    //if (x != 0)
    //{
    //    printf("Type preparser failed!\n");
    //    return 0;
    //}

    yyin = fopen(args[1], "r");
    if (!yyin)
        return 0;
    yycurrentfilename = args[1];
    type_currentfilename = args[1];
    int p = yyparse();
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
