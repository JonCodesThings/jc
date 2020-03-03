%define api.prefix {type_}
%{
#include <stdio.h>
#include <vector>
#include <string>
#include <include/TypeRegistry.hpp>
extern TypeRegistry *registry;
extern int type_lex();
extern int type_parse();
extern std::vector<std::string> identifier_stack;

void type_error (char *error)
{
printf("%s\n", error);
}
%}

%union
{
const char *string;
}

%token STRUCT_TYPE_KEYWORD ALIAS_TYPE_KEYWORD TYPEDEF_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD NONE

%type<string> struct_def alias_def typedef_def

%start stuff

%%

any: defs | SEMICOLON_TYPE_KEYWORD | IDENTIFIER_TYPE_KEYWORD | NONE;

stuff: any | stuff any

defs: struct_def | alias_def | typedef_def

struct_def: STRUCT_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD;

alias_def: ALIAS_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD 
{ registry->AddAlias(identifier_stack[1], identifier_stack[0]);
};

typedef_def: TYPEDEF_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD IDENTIFIER_TYPE_KEYWORD SEMICOLON_TYPE_KEYWORD;

none: NONE { /*printf("none\n");*/ }

;

%%