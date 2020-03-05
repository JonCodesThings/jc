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
<<EOF>> { return 0; }
[  \n\t] {  }
";" {  return SEMICOLON_TYPE_KEYWORD; identifier_stack.clear(); }
"struct" { identifier_stack.clear(); return STRUCT_TYPE_KEYWORD; }
"alias"  { identifier_stack.clear();  return ALIAS_TYPE_KEYWORD; }
"typedef" { identifier_stack.clear(); return TYPEDEF_TYPE_KEYWORD; }
[a-zA-Z0-9]+ { identifier_stack.push_back(yytext); return IDENTIFIER_TYPE_KEYWORD; }
. { return NONE; }
%%