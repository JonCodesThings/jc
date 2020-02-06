%{
#include <stdio.h>
#include <math.h>
#include "jc_lex.hpp"
#include <include/AST.hpp>
#include <vector>

#ifdef PARSER_DRIVER

ASTBlock *base;
extern int yylex();
extern int yyparse();
void yyerror (char *error)
{
printf("%s\n", error);
}
int yywrap() { return 1; }
int main(int argc, char *argv[])
{
yyin = fopen(argv[1], "r");
yyparse();
if (base)
base->EmitIR();
return 0;
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
ASTBlock *scope_block;
ASTIdentifier *id;
const char *string;
int integer;
int token;
}

%token IDENTIFIER STRING INTEGER FLOAT

%token LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET

%token COMMA FSTOP SEMICOLON

%token PLUS MINUS ASTERISK FORWARD_SLASH

%token EQUAL EQUAL_EQUAL

%token EXCLAMATION EXCLAMATION_EQUAL

%token GREATER GREATER_EQUAL

%token LESSER LESSER_EQUAL

%token AND AND_AND

%token OR OR_OR

%token RETURN

%token UNKNOWN

%type<function_definition> function_def
%type<statement> statement
%type<id> id
%type<string> IDENTIFIER
%type<statement> return_statement
%type<scope_block> statements scope

%start module

%%

module: function_def { base = new ASTBlock(); base->block.push_back($1); };

function_def: id id LEFT_BRACKET RIGHT_BRACKET scope { 
$$ = new ASTFunctionDefinition(*$1, *$2, *new std::vector<const char *>(), *$5); };

scope: LEFT_BRACE statements RIGHT_BRACE { $$ = $2; } | LEFT_BRACE RIGHT_BRACE { $$ = new ASTBlock(); } ;

statements: statements statement { $1->block.push_back($2); } 
| statement { $$ = new ASTBlock(); $$->block.push_back($1); };

statement: return_statement;

return_statement: RETURN INTEGER SEMICOLON { auto integer_constant = new ASTConstant<int>(yylval.integer); $$ = new ASTReturnStatement(*integer_constant); }

id: IDENTIFIER { $$ = new ASTIdentifier($1); };

%%
