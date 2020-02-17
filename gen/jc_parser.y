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
ASTConstantInt *constant_int;
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

%type<statement> node_setup semicoloned_statement statement function_def function_decl variable_decl assign_op variable_assign unary_op binary_op
%type<statement> assignable_statement array_decl
%type<unary_operator> cast increment decrement address_of dereference
%type<function_args> arg_list
%type<function_call> function_call
%type<id> id
%type<string> IDENTIFIER
%type<statement> return_statement
%type<scope_block> statements scope semicoloned_statements
%type<statement> add subtract
%type<statement_list> statement_list 
%type<constant> constant
%type<constant_int> constant_int
%type<function_arg> arg_pair
%type<node> id_or_constant

%start module

%%

module: statements { base = new ASTBlock(); base->block.push_back($1); };

statements: node_setup { $$ = new ASTBlock(); $$->block.push_back($1); };
    | statements node_setup { $1->block.push_back($2); };

node_setup: statement { SetNodeInfo(*$$); };

semicoloned_statements: semicoloned_statement { $$ = new ASTBlock(); $$->block.push_back($1); SetNodeInfo(*$$); };
    | semicoloned_statements semicoloned_statement { $1->block.push_back($2); };

semicoloned_statement: statement SEMICOLON { SetNodeInfo(*$1); }; | assignable_statement SEMICOLON { SetNodeInfo(*$1); };

statement: return_statement | function_def | function_decl | variable_decl | assign_op;

assignable_statement: function_call | unary_op | binary_op | id_or_constant;

scope: LEFT_BRACE semicoloned_statements RIGHT_BRACE { $$ = $2; } | LEFT_BRACE RIGHT_BRACE { $$ = new ASTBlock(); } ;

unary_op: cast | increment | decrement | address_of | dereference | array_index;

binary_op: add { $$ = $1;  } | subtract { $$ = $1; };

assign_op: variable_assign;

variable_assign: id EQUAL assignable_statement { $$ = new ASTVariableAssignment(*$1, *$3);  };

cast: LEFT_BRACKET id RIGHT_BRACKET id_or_constant { $$ = new ASTUnaryOperator(*$4, $2, ASTUnaryOperator::CAST); };

increment: id_or_constant PLUS PLUS { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::INCREMENT);  };

decrement: id_or_constant MINUS MINUS { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::DECREMENT);  };

address_of: AND id { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::ADDRESS_OF); };

dereference: ASTERISK id { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::DEREFERENCE); };

array_index: id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::ARRAY_INDEX); };

add: id_or_constant PLUS id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD);  }
    | id_or_constant PLUS unary_op {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD); };

subtract: id_or_constant MINUS id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::SUBTRACT);  };

function_def: id id LEFT_BRACKET arg_list RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *$4, *$6);  }
    | id id LEFT_BRACKET RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *new ASTFunctionArgs(), *$5);  };

function_decl: id id LEFT_BRACKET RIGHT_BRACKET { $$ = new ASTFunctionDeclaration(*$1, *$2, *new ASTFunctionArgs());  };

function_call: id LEFT_BRACKET RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1); }
    | id LEFT_BRACKET statement_list RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1, *$3); };

variable_decl: id id { $$ = new ASTVariableDeclaration(*$1, *$2);  }
    | id id EQUAL assignable_statement { $$ = new ASTVariableDeclaration(*$1, *$2, *$4);  }
    | array_decl;

array_decl: id id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTVariableDeclaration(*$1, *$2, *$4); }

return_statement: RETURN constant { $$ = new ASTReturnStatement(*$2);  }
    | RETURN id { $$ = new ASTReturnStatement(*$2);  };

arg_list: arg_list COMMA arg_pair {  $1->args.push_back(*$3); }
    | arg_pair { $$ = new ASTFunctionArgs(); $$->args.push_back(*$1); };

statement_list: statement_list COMMA statement { $1->push_back($3); }
    | statement { $$ = new std::vector<ASTStatement *>(); $$->push_back($1); };

arg_pair: id id { $$ = new ASTFunctionArg(*$1, *$2); };

id_or_constant: id | constant;

constant: constant_int | FLOAT { $$ = new ASTConstantFloat(yylval.fl); };

constant_int: INTEGER { $$ = new ASTConstantInt(yylval.integer); };

id: IDENTIFIER { $$ = new ASTIdentifier($1); } | id ASTERISK { $1->identifier.append("*"); printf("%s\n", $1->identifier.c_str());  };

%%
