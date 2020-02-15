%{
#include <stdio.h>
#include <math.h>
#include <vector>
#include <include/AST.hpp>

ASTBlock *base;

extern int yylex();
extern int yyparse();
extern unsigned int yylineno;
extern unsigned int yycurrentlinechar;

void yyerror (char *error)
{
printf("%s\n", error);
}

void SetNodeInfo(ASTNode &node)
{
    node.line_number = yylineno;
    node.start_char = yycurrentlinechar;
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
ASTFunctionArg *function_arg;
ASTFunctionArgs *function_args;
ASTFunctionCall *function_call;
ASTFunctionDeclaration *function_declaration;
ASTFunctionDefinition *function_definition;
ASTUnaryOperator *unary_operator;
ASTBlock *scope_block;
ASTConstant *constant;
ASTIdentifier *id;
const char *string;
std::vector<ASTStatement *> *statement_list;
int integer;
float fl;
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

%type<statement> node_setup statement function_def function_decl variable_decl assign_op variable_assign unary_op binary_op statement_id_or_constant
%type<unary_operator> cast increment decrement
%type<function_args> arg_list
%type<function_call> function_call
%type<id> id
%type<string> IDENTIFIER
%type<statement> return_statement
%type<scope_block> statements scope
%type<statement> add subtract
%type<statement_list> statement_id_or_constant_list
%type<constant> constant
%type<function_arg> arg_pair
%type<node> id_or_constant

%start module

%%

module: statements { base = new ASTBlock(); base->block.push_back($1); };

statements: node_setup { $$ = new ASTBlock(); $$->block.push_back($1); };
    | statements node_setup { $1->block.push_back($2); };

node_setup: statement { SetNodeInfo(*$$); };

statement: return_statement | function_call_standalone | function_call | function_def | function_decl | variable_decl | assign_op | unary_op | binary_op | scope | id_or_constant SEMICOLON;

scope: LEFT_BRACE statements RIGHT_BRACE { $$ = $2; } | LEFT_BRACE RIGHT_BRACE { $$ = new ASTBlock(); } ;

unary_op: cast | increment | decrement;

binary_op: add { $$ = $1;  } | subtract { $$ = $1; };

assign_op: variable_assign;

variable_assign: id EQUAL statement { $$ = new ASTVariableAssignment(*$1, *$3);  };

cast: LEFT_BRACKET id RIGHT_BRACKET id_or_constant SEMICOLON { $$ = new ASTUnaryOperator(*$4, $2, ASTUnaryOperator::CAST); };

increment: id_or_constant PLUS PLUS SEMICOLON { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::INCREMENT);  };

decrement: id MINUS MINUS SEMICOLON { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::DECREMENT);  };

add: id_or_constant PLUS id_or_constant SEMICOLON { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD);  }
    | id_or_constant PLUS unary_op SEMICOLON {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD); };

subtract: id MINUS id SEMICOLON { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::SUBTRACT);  };

function_def: id id LEFT_BRACKET arg_list RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *$4, *$6);  }
    | id id LEFT_BRACKET RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *new ASTFunctionArgs(), *$5);  }

function_decl: id id LEFT_BRACKET RIGHT_BRACKET SEMICOLON { $$ = new ASTFunctionDeclaration(*$1, *$2, *new ASTFunctionArgs());  };

function_call_standalone: function_call SEMICOLON

function_call: id LEFT_BRACKET RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1); }
    | id LEFT_BRACKET statement_id_or_constant_list RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1, *$3); };

variable_decl: id id SEMICOLON { $$ = new ASTVariableDeclaration(*$1, *$2);  }
    | id id EQUAL statement { $$ = new ASTVariableDeclaration(*$1, *$2, *$4);  };

return_statement: RETURN constant SEMICOLON { $$ = new ASTReturnStatement(*$2);  };
    | RETURN id SEMICOLON { $$ = new ASTReturnStatement(*$2);  };

arg_list: arg_list COMMA arg_pair {  $1->args.push_back(*$3); }
    | arg_pair { $$ = new ASTFunctionArgs(); $$->args.push_back(*$1); };

statement_id_or_constant_list: statement_id_or_constant_list COMMA statement_id_or_constant { $1->push_back($3); }
    | statement_id_or_constant { $$ = new std::vector<ASTStatement *>(); $$->push_back($1); };

statement_id_or_constant: statement | id | constant

arg_pair: id id { $$ = new ASTFunctionArg(*$1, *$2); };

id_or_constant: id | constant;

constant: INTEGER { $$ = new ASTConstantInt(yylval.integer);};

id: IDENTIFIER { $$ = new ASTIdentifier($1);  };

%%
