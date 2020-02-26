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
ASTIfStatement *if_statement;
ASTWhileStatement *while_loop;
ASTUnaryOperator *unary_operator;
ASTBlock *scope_block;
ASTConstant *constant;
ASTConstantInt *constant_int;
ASTIdentifier *id;
const char *string;
std::vector<ASTConditionalBlock *> *cond_block;
std::vector<ASTStatement *> *statement_list;
int integer;
float fl;
int token;
}

%token IDENTIFIER STRING INTEGER FLOAT TYPE

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

%token IF ELSE

%token FOR WHILE

%token EXTERN

%token UNKNOWN

%type<statement> node_setup semicoloned_statement statement function_def function_decl variable_decl assign_op variable_assign unary_op binary_op
%type<statement> assignable_statement array_decl
%type<unary_operator> cast increment decrement address_of dereference array_index
%type<function_args> arg_list
%type<function_call> function_call
%type<if_statement> if_statement
%type<id> id type
%type<string> IDENTIFIER TYPE
%type<statement> return_statement flow_control
%type<scope_block> statements scope semicoloned_statements
%type<statement> add subtract multiply divide equality inequality
%type<statement_list> statement_list
%type<cond_block> cond_block
%type<while_loop> while_loop
%type<constant> constant
%type<constant_int> constant_int
%type<function_arg> arg_pair
%type<node> id_or_constant

%start module

%%

module: statements { base = new ASTBlock(); base->block.push_back($1); };

statements: node_setup { $$ = new ASTBlock(); $$->block.push_back($1); };
    | statements node_setup { $1->block.push_back($2); };

node_setup: statement { SetNodeInfo(*$$); } | statement SEMICOLON { SetNodeInfo(*$$); };

semicoloned_statements: semicoloned_statement { $$ = new ASTBlock(); $$->block.push_back($1); SetNodeInfo(*$$); }
    | semicoloned_statements semicoloned_statement { $1->block.push_back($2); };

semicoloned_statement: statement SEMICOLON { SetNodeInfo(*$1); }; | assignable_statement SEMICOLON { SetNodeInfo(*$1); } | flow_control { SetNodeInfo(*$1); };

statement: return_statement | function_def | function_decl | variable_decl | assign_op | flow_control;

assignable_statement: function_call | unary_op | binary_op | id_or_constant;

flow_control: if_statement | loop;

loop: while_loop;

scope: LEFT_BRACE semicoloned_statements RIGHT_BRACE { $$ = $2; } | LEFT_BRACE RIGHT_BRACE { $$ = new ASTBlock(); } ; 

unary_op: cast | increment | decrement | address_of | dereference | array_index;

binary_op: add | subtract | multiply | divide | equality | inequality;

assign_op: variable_assign;

variable_assign: id EQUAL assignable_statement { $$ = new ASTVariableAssignment(*$1, *$3);  }
    | array_index EQUAL assignable_statement { $$ = new ASTVariableAssignment(*$1, *$3); };

cast: LEFT_BRACKET id RIGHT_BRACKET id_or_constant { $$ = new ASTUnaryOperator(*$4, $2, ASTUnaryOperator::CAST); };

increment: id_or_constant PLUS PLUS { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::INCREMENT);  };

decrement: id_or_constant MINUS MINUS { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::DECREMENT);  };

address_of: AND id { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::ADDRESS_OF); };

dereference: ASTERISK id { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::DEREFERENCE); };

array_index: id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTUnaryOperator(*$1, *$3, ASTUnaryOperator::ARRAY_INDEX); }
    | id LEFT_SQUARE_BRACKET id RIGHT_SQUARE_BRACKET { $$ = new ASTUnaryOperator(*$1, $3, ASTUnaryOperator::ARRAY_INDEX);} ;

add: id_or_constant PLUS id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD);  }
    | id_or_constant PLUS unary_op {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::ADD); };

subtract: id_or_constant MINUS id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::SUBTRACT);  }
    | id_or_constant MINUS unary_op { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::SUBTRACT); };

multiply: id_or_constant ASTERISK id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::MULTIPLY);  }
    | id_or_constant ASTERISK unary_op {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::MULTIPLY); };

divide: id_or_constant FORWARD_SLASH id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::DIVIDE);  }
    | id_or_constant FORWARD_SLASH unary_op {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::DIVIDE); };

equality: id_or_constant EQUAL_EQUAL id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::EQUALITY);  }
    | id_or_constant EQUAL_EQUAL unary_op {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::EQUALITY); };

inequality: id_or_constant EXCLAMATION_EQUAL id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::INEQUALITY);  }
    | id_or_constant EXCLAMATION_EQUAL unary_op {$$ = new ASTBinaryOperator(*$1, *$3, ASTBinaryOperator::INEQUALITY); };

function_def: type id LEFT_BRACKET arg_list RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *$4, *$6);  }
    | type id LEFT_BRACKET RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *new ASTFunctionArgs(), *$5);  };

function_decl: type id LEFT_BRACKET RIGHT_BRACKET SEMICOLON { $$ = new ASTFunctionDeclaration(*$1, *$2, *new ASTFunctionArgs());  }
    | type id LEFT_BRACKET arg_list RIGHT_BRACKET SEMICOLON { $$ = new ASTFunctionDeclaration(*$1, *$2, *$4);  }
    | EXTERN function_decl SEMICOLON;

function_call: id LEFT_BRACKET RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1); }
    | id LEFT_BRACKET statement_list RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1, *$3); printf("oof\n"); };

variable_decl: type id { $$ = new ASTVariableDeclaration(*$1, *$2);  }
    | type id EQUAL assignable_statement { $$ = new ASTVariableDeclaration(*$1, *$2, *$4);  }
    | array_decl;

array_decl: type id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTVariableDeclaration(*$1, *$2, *$4); }

return_statement: RETURN assignable_statement { $$ = new ASTReturnStatement(*$2); };

if_statement: cond_block { $$ = new ASTIfStatement(*$1, NULL); } | cond_block ELSE scope { $$ = new ASTIfStatement(*$1, $3); }

cond_block: IF LEFT_BRACKET assignable_statement RIGHT_BRACKET scope 
    { 
        $$ = new std::vector<ASTConditionalBlock*>();
        ASTConditionalBlock *cb = new ASTConditionalBlock(*$3, *$5);
        $$->push_back(cb);
    }
    | cond_block ELSE IF LEFT_BRACKET assignable_statement RIGHT_BRACKET scope
    {
        ASTConditionalBlock *cb = new ASTConditionalBlock(*$5, *$7);
        $1->push_back(cb);
    }

while_loop: WHILE LEFT_BRACKET assignable_statement RIGHT_BRACKET scope { $$ = new ASTWhileStatement(*$3, *$5); };

arg_list: arg_list COMMA arg_pair {  $1->args.push_back(*$3); }
    | arg_pair { $$ = new ASTFunctionArgs(); $$->args.push_back(*$1); };

statement_list: statement_list COMMA assignable_statement { $1->push_back($3); printf("why\n"); }
    | assignable_statement { $$ = new std::vector<ASTStatement *>(); $$->push_back($1); printf("why\n"); };

arg_pair: type id { $$ = new ASTFunctionArg(*$1, *$2); };

id_or_constant: id | constant;

constant: constant_int | FLOAT { $$ = new ASTConstantFloat(yylval.fl); } | STRING { $$ = new ASTConstantString(yylval.string); };

constant_int: INTEGER { $$ = new ASTConstantInt(yylval.integer); };

id: IDENTIFIER { $$ = new ASTIdentifier($1); };

type: TYPE { $$ = new ASTIdentifier($1); } | type ASTERISK { $1->identifier.append("*");  };

%%
