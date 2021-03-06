%option nounistd
%option never-interactive
%option outfile="gen/jc_lex.cpp"
%option header-file= "gen/jc_lex.hpp"
%{
#include <include/AST.hpp>
#include "jc_parser.hpp"
extern "C" int yywrap() { return 1; }
unsigned int yycurrentlinechar = 0;
const char *yycurrentfilename = "";
TypeRegistry *registry;
%}


%%
"\n" { yylineno++; /*printf("%d\n", yylineno);*/ yycurrentlinechar = 0; }
[  \t] { /*printf("skipping whitespace\n");*/ yycurrentlinechar += yyleng; }
"//".* { printf("skipping whitespace\n"); yycurrentlinechar += yyleng; }
\"[^"]*\" { yylval.string = yytext; return STRING; yycurrentlinechar += yyleng; }
[0-9]+ { yylval.integer = atoi(yytext); return INTEGER; yycurrentlinechar += yyleng; }
[+-]?([0-9]*[.])?[0-9]+"f" { yylval.fl = atof(yytext); return FLOAT; yycurrentlinechar += yyleng; }

"->" { return ARROW; yycurrentlinechar += yyleng; }

"(" { return LEFT_BRACKET; yycurrentlinechar += yyleng; }
")" { return RIGHT_BRACKET; yycurrentlinechar += yyleng; }
"{" { return LEFT_BRACE; yycurrentlinechar += yyleng; }
"}" { return RIGHT_BRACE; yycurrentlinechar += yyleng; }
"[" { return LEFT_SQUARE_BRACKET; yycurrentlinechar += yyleng; }
"]" { return RIGHT_SQUARE_BRACKET; yycurrentlinechar += yyleng; }

"," { return COMMA; yycurrentlinechar += yyleng; }
"." { return FSTOP; yycurrentlinechar += yyleng; }
";" { return SEMICOLON; yycurrentlinechar += yyleng; }
":" { return COLON; yycurrentlinechar += yyleng; }

"+" { return PLUS; yycurrentlinechar += yyleng; }
"-" { return MINUS; yycurrentlinechar += yyleng; }
"/" { return FORWARD_SLASH; yycurrentlinechar += yyleng; }
"*" { return ASTERISK; yycurrentlinechar += yyleng; }

"=" { return EQUAL; yycurrentlinechar += yyleng; }
"==" { return EQUAL_EQUAL; yycurrentlinechar += yyleng; }

"!" { return EXCLAMATION; yycurrentlinechar += yyleng; }
"!=" { return EXCLAMATION_EQUAL; yycurrentlinechar += yyleng; }

">" { return GREATER; yycurrentlinechar += yyleng; }
">=" { return GREATER_EQUAL; yycurrentlinechar += yyleng; }

"<" { return LESSER; yycurrentlinechar += yyleng; }
"<=" { return LESSER_EQUAL; yycurrentlinechar += yyleng; }

"&" { return AND; yycurrentlinechar += yyleng; }
"&&" { return AND_AND; yycurrentlinechar += yyleng; }

"|" { return OR; yycurrentlinechar += yyleng; }
"||" { return OR_OR; yycurrentlinechar += yyleng; }

"<<" { return LEFT_SHIFT; yycurrentlinechar += yyleng; }
">>" { return RIGHT_SHIFT; yycurrentlinechar += yyleng; }

"import" { return IMPORT; yycurrentlinechar += yyleng; }
"return" { return RETURN; yycurrentlinechar += yyleng; }
"extern" { return EXTERN; yycurrentlinechar += yyleng; }
"if" { return IF; yycurrentlinechar += yyleng; }
"else" { return ELSE; yycurrentlinechar += yyleng; }
"for" { return FOR; yycurrentlinechar += yyleng; }
"while" { return WHILE; yycurrentlinechar += yyleng; }
"struct" { return STRUCT; yycurrentlinechar += yyleng; }
"defer" { return DEFER; yycurrentlinechar += yyleng; }
"alias" { return ALIAS; yycurrentlinechar += yyleng; }
"typedef" { return TYPEDEF; yycurrentlinechar += yyleng; }
"export" { return EXPORT; yycurrentlinechar += yyleng; }
"include" { return INCLUDE; yycurrentlinechar += yyleng; }
"link" { return LINK; ; yycurrentlinechar += yyleng; }
"auto" { return AUTO; yycurrentlinechar += yyleng; }
"func_ptr" { return FUNC_PTR; yycurrentlinechar += yyleng; }
"nullptr" { return NULLPTR; yycurrentlinechar += yyleng; }
"union" { return UNION; yycurrentlinechar += yyleng; }
"enum" { return ENUM; yycurrentlinechar += yyleng; }
"true" { return TRUE; yycurrentlinechar += yyleng; }
"false" { return FALSE; yycurrentlinechar += yyleng; }
[_a-zA-Z0-9]+ { yylval.string = yytext; if (!registry->GetTypeInfo(yylval.string)) return IDENTIFIER; else return TYPE; yycurrentlinechar += yyleng; }

. { return UNKNOWN; }
<<EOF>> { return 0; }
%%
#define YY_NO_UNISTD_H 1

#ifdef SCANNER_DRIVER

#include <vector>

int yywrap() { return 1; }
int main(int argc, char *argv[])
{
yyin = fopen(argv[1], "r");
int token = 0;
std::vector<int> tokens;
while (token = yylex())
{
if (token != 1)
{
printf("Token: %d  Text: %s\n", token, yytext);
tokens.push_back(token);
}
}

return 0;
}

#endif
