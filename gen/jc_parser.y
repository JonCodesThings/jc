%{
#include <stdio.h>
#include <math.h>
#include "jc_lex.hpp"
#include <include/AST.hpp>

#ifdef PARSER_DRIVER

#include <vector>

ASTBlock *block;
extern int yylex();
extern int yyparse();
void yyerror (char *error)
{
printf(error);
}
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
yyparse();
}

#endif
%}

%union
{
ASTNode *node;
ASTStatement *statement;
ASTExpression *expression;
ASTConstant<const char *> *string_constant;
ASTFunctionCall *function_call;
ASTFunctionDeclaration *function_declaration;
ASTFunctionDefinition *function_definition;
ASTIdentifier *identifier;
const char *string;
int token;
}

%token <string> STRING
%token <token> COMMA SEMICOLON LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE RETURN

%token <identifier> identifier
%token <expression> expression

%start module

%%

module: statements { block = $1; printf("oof\n"); };

statements: statements statement | statement;

statement: function_def | expr | function_call;

expr: return_scope;

return_scope: RETURN identifier;

function_def: identifier identifier arg_list block;

function_call: identifier parameter_list;

arg_list: arg
| '(' arg ')';

arg: identifier COMMA identifier
	| arg COMMA arg;
	
parameter_list : parameter
| '(' parameter ')';

parameter: identifier
	| arg COMMA parameter;

block: LEFT_BRACE statements RIGHT_BRACE;
%%
