#include <include/AST.hpp>
#include <gen/jc_parser.hpp>
#include <include/IREmitter.hpp>

extern ASTBlock *base;
extern FILE *yyin;
extern int yyparse();


int main(int argc, const char **args)
{
yyin = fopen(args[1], "r");
printf("%s\n", args[1]);
int p = yyparse();
if (base)
{
llvm::LLVMContext context;
base->EmitIR();
}
return 0;
}
