%option nounistd
%option never-interactive
%option outfile="gen/jc_type_scanner.cpp"
%option header-file= "gen/jc_type_scanner.hpp"
%option prefix="type_"
%{
#include "jc_type_parser.hpp"
extern "C" int type_wrap() { return 1; }
%}

%%
"struct" { return STRUCT_TYPE_KEYWORD; }
"alias"  { return ALIAS_TYPE_KEYWORD; }
"typedef" { return TYPEDEF_TYPE_KEYWORD; }
";" { return SEMICOLON_TYPE_KEYWORD; }
[a-zA-Z0-9]+ { type_lval.string = yytext; return IDENTIFIER_TYPE_KEYWORD; }
%%