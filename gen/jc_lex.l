%option nounistd
%option never-interactive
%option outfile="gen/jc_lex.cpp"
%option header-file= "gen/jc_lex.hpp"
%{
#include <include/AST.hpp>
#include "jc_parser.hpp"
extern "C" int yywrap() { printf("wrap\n"); return 1; }


%}


%%
[[:space:]]+ { /*printf("skipping whitespace\n");*/ }
\"[^"]*\" { yylval.string = yytext; return STRING; }
[0-9]+ { yylval.integer = atoi(yytext); return INTEGER; }

"(" { return LEFT_BRACKET; }
")" { return RIGHT_BRACKET; }
"{" { return LEFT_BRACE; }
"}" { return RIGHT_BRACE; }
"[" { return LEFT_SQUARE_BRACKET; }
"]" { return RIGHT_SQUARE_BRACKET; }

"," { return COMMA; }
"." { return FSTOP; }
";" { return SEMICOLON; }

"+" { return PLUS; }
"-" { return MINUS; }
"/" { return FORWARD_SLASH; }
"*" { return ASTERISK; }

"=" { return EQUAL; }
"==" { return EQUAL_EQUAL; }

"!" { return EXCLAMATION; }
"!=" { return EXCLAMATION_EQUAL; }

">" { return GREATER; }
">=" { return GREATER_EQUAL; }

"<" { return LESSER; }
"<=" { return LESSER_EQUAL; }

"&" { return AND; }
"&&" { return AND_AND; }

"|" { return OR; }
"||" { return OR_OR; }

"return" { return RETURN; }
[a-zA-Z0-9]+ { yylval.string = yytext; return IDENTIFIER; }

. { return UNKNOWN; }
<<EOF>> { return 0; }
%%


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
