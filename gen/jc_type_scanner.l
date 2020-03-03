%option nounistd
%option never-interactive
%option outfile="gen/jc_type_scanner.cpp"
%option header-file= "gen/jc_type_scanner.hpp"
%option prefix="type_"
%{
#include <vector>
#include <string>
#include "jc_type_parser.hpp"
const char *type_currentfilename = "";
extern "C" int type_wrap() { return 1; }
std::vector<std::string> identifier_stack;
%}

%%
"struct" { identifier_stack.clear(); return STRUCT_TYPE_KEYWORD; }
"alias"  { identifier_stack.clear(); /*printf("yikes\n");*/ return ALIAS_TYPE_KEYWORD; }
"typedef" { identifier_stack.clear(); return TYPEDEF_TYPE_KEYWORD; }
";" { /*printf("semicolon\n");*/ return SEMICOLON_TYPE_KEYWORD; identifier_stack.clear(); }
[a-zA-Z0-9]+ { identifier_stack.push_back(yytext); /*printf("%s\n", yytext);*/ return IDENTIFIER_TYPE_KEYWORD; }
[  \t\n] { /*printf("skipping whitespace\n");*/ }
. { return NONE; }
<<EOF>> { return 0; }
%%