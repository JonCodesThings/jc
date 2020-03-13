#include <include/AST.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>
#include <include/TypeTokenizer.hpp>

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
	TypeTokenizer type(*registry);
    registry->SetupBuiltinJCTypes();
	std::ifstream t_in(args[1]);
	std::string t_string((std::istreambuf_iterator<char>(t_in)), std::istreambuf_iterator<char>());
	type.Tokenize(t_string);
    yyin = fopen(args[1], "r");
    if (!yyin)
        return 0;
    yycurrentfilename = args[1];
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
