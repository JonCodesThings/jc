#include <include/AST.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/raw_ostream.h>

#include <fstream>

extern ASTBlock *base;
extern FILE *yyin;
extern int yyparse();


int main(int argc, const char **args)
{
    yyin = fopen(args[1], "r");
    int p = yyparse();
    if (base)
    {
        llvm::LLVMContext context;
        llvm::Module module("jc alpha", context);
        IREmitter emitter(module, context);

        if (emitter.EmitIR(base))
        {
            std::error_code ec;
            llvm::raw_fd_ostream out("alpha.ir", ec);
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
