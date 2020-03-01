#include <include/AST.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

#include <fstream>

extern ASTBlock *base;
extern FILE *yyin;
extern const char *yycurrentfilename;
extern int yyparse();
extern TypeRegistry *registry;


int main(int argc, const char **args)
{
    yyin = fopen(args[1], "r");
    if (!yyin)
        return 0;
    yycurrentfilename = args[1];
    llvm::LLVMContext context;
    registry = new TypeRegistry(context);
    registry->SetupBuiltinJCTypes();
    int p = yyparse();
    if (base)
    {
        llvm::Module module("jc alpha", context);
        IREmitter emitter(module, context, *registry);

        if (emitter.EmitIR(base))
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
