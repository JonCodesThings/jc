%define api.prefix {type_}
%{
#include <include/TypeRegistry.hpp>
extern TypeRegistry *registry;
extern int type_lex();
extern int type_parse();

void type_error (char *error)
{
printf("%s\n", error);
}
%}

%union
{
const char *string;
}

%token STRUCT_TYPE_KEYWORD ALIAS_TYPE_KEYWORD TYPEDEF_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD

%type<string> struct_def alias_def typedef_def

%%

struct_def: STRUCT_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD;

alias_def: ALIAS_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD;

typedef_def: TYPEDEF_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD;

%%