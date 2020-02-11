%{
#include <stdio.h>
#include <math.h>
#include <vector>
#include <include/AST.hpp>

ASTBlock *base;

extern int yylex();
extern int yyparse();

void yyerror (char *error)
{
printf("%s\n", error);
}


#ifdef PARSER_DRIVER

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
ASTUnaryOperator *unary_operator;
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

%type<statement> statement function_def function_decl variable_decl assign_op variable_assign unary_op binary_op
%type<unary_operator> increment decrement
%type<id> id
%type<string> IDENTIFIER
%type<statement> return_statement
%type<scope_block> statements scope
%type<statement> add subtract

%start module

%%

module: function_def { base = new ASTBlock(); base->block.push_back($1); };

scope: LEFT_BRACE statements RIGHT_BRACE { $$ = $2; } | LEFT_BRACE RIGHT_BRACE { $$ = new ASTBlock(); } ;

statements: statements statement { $1->block.push_back($2); } 
| statement { $$ = new ASTBlock(); $$->block.push_back($1); };

statement: return_statement | function_def | function_decl | variable_decl | assign_op | unary_op | binary_op;

unary_op: increment | decrement;

binary_op: add | subtract;

assign_op: variable_assign;

variable_assign: id EQUAL INTEGER SEMICOLON { auto integer_constant = new ASTConstant<int>(yylval.integer); $$ = new ASTVariableAssignment(*$1, *integer_constant); }
    | id EQUAL id SEMICOLON { $$ = new ASTVariableAssignment(*$1, *$3); }
    | id EQUAL statement { $$ = new ASTVariableAssignment(*$1, *$3); };

increment: id PLUS PLUS SEMICOLON { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::INCREMENT); };

decrement: id MINUS MINUS SEMICOLON { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::DECREMENT); };

add: id PLUS id SEMICOLON { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD); };

subtract: id MINUS id SEMICOLON { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::SUBTRACT); };

function_def: id id LEFT_BRACKET RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *new std::vector<const char *>(), *$5); };

function_decl: id id LEFT_BRACKET RIGHT_BRACKET SEMICOLON { $$ = new ASTFunctionDeclaration(*$1, *$2, *new std::vector<const char *>()); };

variable_decl: id id SEMICOLON { $$ = new ASTVariableDeclaration(*$1, *$2); };

return_statement: RETURN INTEGER SEMICOLON { auto integer_constant = new ASTConstant<int>(yylval.integer); $$ = new ASTReturnStatement(*integer_constant); }
    | RETURN id SEMICOLON { $$ = new ASTReturnStatement(*$2); };

id: IDENTIFIER { $$ = new ASTIdentifier($1); };

%%
