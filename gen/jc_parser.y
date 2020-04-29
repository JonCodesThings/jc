%{
#include <stdio.h>
#include <math.h>
#include <vector>
#include <include/AST.hpp>

std::unique_ptr<ASTBlock> base;

extern int yylex();
extern int yyparse();
extern int yylineno;
extern unsigned int yycurrentlinechar;
extern const char *yycurrentfilename;
extern TypeRegistry *registry;

void yyerror (char *error)
{
printf("%s in filename %s at line %d\n", error, yycurrentfilename, yylineno);
}

void SetNodeInfo(ASTNode &node)
{
    node.line_number = yylineno;
    node.start_char = yycurrentlinechar;
	node.filename = yycurrentfilename;
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
ASTDeferredStatement *defer_statement;
ASTExpression *expression;
ASTFunctionArg *function_arg;
ASTFunctionArgs *function_args;
ASTFunctionPointerDefinition *func_ptr;
ASTStructMemberDeclaration *struct_decl;
ASTStructMemberDeclarations *struct_declarations;
ASTFunctionCall *function_call;
ASTFunctionDeclaration *function_declaration;
ASTFunctionDefinition *function_definition;
ASTStructDeclaration *struct_declaration;
ASTStructDefinition *struct_definition;
ASTVariableDeclaration *variable_declaration;
ASTMemberOperator *member_operator;
ASTIfStatement *if_statement;
ASTForStatement *for_loop;
ASTEnumDefinition *enum_def;
ASTUnionDefinition *union_def;
ASTEnumPart *enum_part;
ASTEnumParts *enum_parts;
ASTConstantEnumValue *enum_val;
ASTWhileStatement *while_loop;
ASTTypeSystemModStatement *type_mod;
ASTUnaryOperator *unary_operator;
ASTBlock *scope_block;
ASTConstant *constant;
ASTConstantInt *constant_int;
ASTIdentifier *id;
const char *string;
std::vector<std::unique_ptr<ASTConditionalBlock>> *cond_block;
std::vector<std::unique_ptr<ASTStatement>> *statement_list;
std::vector<std::unique_ptr<ASTIdentifier>> *type_list;
std::vector<std::unique_ptr<ASTNode>> *node_list;
int integer;
float fl;
int token;
}

%token IDENTIFIER STRING INTEGER FLOAT TYPE

%token LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET

%token COMMA FSTOP SEMICOLON COLON

%token PLUS MINUS ASTERISK FORWARD_SLASH PERCENT

%token EQUAL EQUAL_EQUAL

%token EXCLAMATION EXCLAMATION_EQUAL

%token GREATER GREATER_EQUAL

%token LESSER LESSER_EQUAL

%token AND AND_AND

%token OR OR_OR

%token LEFT_SHIFT RIGHT_SHIFT

%token RETURN DEFER

%token IF ELSE

%token FOR WHILE

%token TYPEDEF ALIAS AUTO ENUM UNION TRUE FALSE MUT

%token EXTERN IMPORT EXPORT INCLUDE LINK FUNC_PTR NULLPTR

%token STRUCT ARROW

%token UNKNOWN

%type<statement> node_setup semicoloned_statement statement assign_op variable_assign unary_op binary_op member_op include_or_link memberable
%type<variable_declaration> array_decl
%type<func_ptr> func_ptr
%type<variable_declaration> variable_decl
%type<function_definition> function_def
%type<function_declaration> function_decl
%type<statement> assignable_statement import
%type<statement> binop
%type<unary_operator> cast increment decrement address_of dereference array_index unary_plus unary_minus
%type<function_args> arg_list 
%type<struct_declarations> struct_list
%type<function_call> function_call
%type<if_statement> if_statement
%type<id> id type composited_type
%type<string> IDENTIFIER TYPE
%type<statement> return_statement flow_control
%type<scope_block> statements scope semicoloned_statements
%type<struct_definition> struct_def
%type<statement_list> statement_list
%type<defer_statement> defer_statement
%type<type_mod> alias_statement typedef_statement
%type<cond_block> cond_block
%type<while_loop> while_loop
%type<for_loop> for_loop
%type<constant> constant
%type<constant_int> constant_int constant_bool
%type<function_arg> arg_pair
%type<struct_decl> struct_pair
%type<node_list> init_list
%type<node> id_or_constant
%type<enum_part> enum_part
%type<enum_parts> enum_parts
%type<enum_def> enum_def
%type<union_def> union_def
%type<type_list> type_list
%type<enum_val> constant_enum_value
%type<struct_declaration> struct_decl
%type<integer> binop_id


%start module

%%

module: statements { /*printf("module base: %s\n", yycurrentfilename);*/ base = std::make_unique<ASTBlock>(); std::unique_ptr<ASTBlock> b = std::unique_ptr<ASTBlock>($1); base->block->push_back(std::move(b)); };

statements: node_setup { /*printf("node_setup\n");*/ $$ = new ASTBlock(); auto s = std::unique_ptr<ASTStatement>($1); $$->block->push_back(std::move(s)); };
    | statements node_setup { /*printf("appending node_setup\n");*/ auto s = std::unique_ptr<ASTStatement>($2); $1->block->push_back(std::move(s)); };

node_setup: statement { /*printf("no semicolon\n");*/ SetNodeInfo(*$$); } | statement SEMICOLON { /*printf("semicolon\n");*/  SetNodeInfo(*$$); }

semicoloned_statements: semicoloned_statement { $$ = new ASTBlock(); auto statement = std::unique_ptr<ASTStatement>($1); $$->block->push_back(std::move(statement)); SetNodeInfo(*$$); }
    | semicoloned_statements semicoloned_statement { auto statement = std::unique_ptr<ASTStatement>($2); $1->block->push_back(std::move(statement)); };

semicoloned_statement: statement SEMICOLON { /*printf("semicoloned statement\n");*/ SetNodeInfo(*$1); }; | assignable_statement SEMICOLON { /*printf("semicoloned assignable statement\n");*/ SetNodeInfo(*$1); } 
	| flow_control { /*printf("flow_control\n");*/ SetNodeInfo(*$1); }
    | defer_statement SEMICOLON { /*printf("semicoloned defer statement\n");*/ SetNodeInfo(*$1); }
    | function_def { /*printf("function_def\n");*/ SetNodeInfo(*$1); } ;

statement: return_statement | function_decl | variable_decl | assign_op | alias_statement | typedef_statement | struct_def | struct_decl | import | include_or_link | func_ptr | enum_def | union_def | flow_control | function_def | struct_decl

alias_statement: ALIAS TYPE TYPE { /*printf("alias");*/ $$ = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::ALIAS); };

typedef_statement: TYPEDEF TYPE TYPE { $$ = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::TYPEDEF); };

struct_def: STRUCT type LEFT_BRACE struct_list RIGHT_BRACE { $$ = new ASTStructDefinition(*$2, *$4); };
	| EXPORT struct_def { $$ = $2; $$->exporting = true; }

struct_decl: STRUCT type { $$ = new ASTStructDeclaration(*$2); };

union_def: UNION type LEFT_BRACE struct_list RIGHT_BRACE { $$ = new ASTUnionDefinition(*$2, *$4); }
	| EXPORT union_def { $$ = $2; $$->exporting = true; };

defer_statement: DEFER assignable_statement { $$ = new ASTDeferredStatement(*$2); }

assignable_statement: function_call | unary_op | binary_op | member_op | id_or_constant;

flow_control: if_statement | loop;

loop: while_loop | for_loop;

scope: LEFT_BRACE semicoloned_statements RIGHT_BRACE { $$ = $2; } | LEFT_BRACE RIGHT_BRACE { $$ = new ASTBlock(); } ;

import: IMPORT id { $$ = new ASTImportStatement(); };

unary_op: cast | increment | decrement | address_of | dereference | array_index | unary_minus | unary_plus;

unary_minus: MINUS id_or_constant { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::MINUS); }

unary_plus: PLUS id_or_constant { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::PLUS); }

binary_op: binop { $$ = $1; }

assign_op: variable_assign;

memberable: id | array_index

array_index: id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTUnaryOperator(*$1, *$3, ASTUnaryOperator::ARRAY_INDEX); }
    | id LEFT_SQUARE_BRACKET id RIGHT_SQUARE_BRACKET { $$ = new ASTUnaryOperator(*$1, $3, ASTUnaryOperator::ARRAY_INDEX);} ;

member_op: memberable FSTOP memberable { $$ = new ASTMemberOperator(*$1, *$3, ASTMemberOperator::OP::DOT); }
	| memberable FSTOP member_op { $$ = new ASTMemberOperator(*$1, *$3, ASTMemberOperator::OP::DOT); }

variable_assign: id EQUAL assignable_statement { $$ = new ASTVariableAssignment(*$1, *$3);  }
    | array_index EQUAL assignable_statement { $$ = new ASTVariableAssignment(*$1, *$3); }
    | member_op EQUAL assignable_statement { $$ = new ASTVariableAssignment(*$1, *$3); };

cast: LEFT_BRACKET composited_type RIGHT_BRACKET id_or_constant { $$ = new ASTUnaryOperator(*$4, $2, ASTUnaryOperator::CAST); };

increment: id_or_constant PLUS PLUS { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::INCREMENT);  };

decrement: id_or_constant MINUS MINUS { $$ = new ASTUnaryOperator(*$1, ASTUnaryOperator::DECREMENT);  };

address_of: AND id { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::ADDRESS_OF); };

dereference: ASTERISK id { $$ = new ASTUnaryOperator(*$2, ASTUnaryOperator::DEREFERENCE); };

binop_id: PLUS { $$ = 0; } | MINUS { $$ = 1; } | ASTERISK { $$ = 2; } 
	| FORWARD_SLASH { $$ = 3; } | EQUAL_EQUAL { $$ = 4; } | EXCLAMATION_EQUAL { $$ = 5; }
	| LESSER { $$ = 6; }| GREATER  { $$ = 7; }| LESSER_EQUAL { $$ = 8; } 
	| GREATER_EQUAL { $$ = 9; }| AND { $$ = 10; } | OR { $$ = 11; }
	| LEFT_SHIFT { $$ = 12; } | RIGHT_SHIFT { $$ = 13; } | PERCENT { $$ = 14; }

binop: id_or_constant binop_id id_or_constant { $$ = new ASTBinaryOperator(*$1, *$3, (ASTBinaryOperator::OP)$2); }
	  | id_or_constant binop_id unary_op {$$ = new ASTBinaryOperator(*$1, *$3, (ASTBinaryOperator::OP)$2); };
	  | unary_op binop_id id_or_constant {$$ = new ASTBinaryOperator(*$1, *$3, (ASTBinaryOperator::OP)$2); };

function_def: composited_type id LEFT_BRACKET arg_list RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *$4, *$6);  }
    | composited_type id LEFT_BRACKET RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$2, *new ASTFunctionArgs(), *$5);  };
	| id LEFT_BRACKET arg_list RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *$3, *$5);  }
	| id LEFT_BRACKET RIGHT_BRACKET scope {  $$ = new ASTFunctionDefinition(*$1, *new ASTFunctionArgs(), *$4);  }
    | EXPORT function_def { $$ = $2; $$->SetExporting(true); };

function_decl: composited_type id LEFT_BRACKET RIGHT_BRACKET SEMICOLON { /*printf("function_decl\n");*/ $$ = new ASTFunctionDeclaration(*$1, *$2, *new ASTFunctionArgs());  }
    | composited_type id LEFT_BRACKET arg_list RIGHT_BRACKET SEMICOLON { /*printf("function_decl\n");*/ $$ = new ASTFunctionDeclaration(*$1, *$2, *$4);  }
    | EXPORT function_decl { $$ = $2; $$->SetExporting(true); };

function_call: id LEFT_BRACKET RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1); }
    | id LEFT_BRACKET statement_list RIGHT_BRACKET { $$ = new ASTFunctionCall(*$1, *$3); };

variable_decl: composited_type id { $$ = new ASTVariableDeclaration(*$1, *$2);  }
	| id COLON EQUAL assignable_statement { $$ = new ASTVariableDeclaration(*$1, *$4); }
    | composited_type id EQUAL assignable_statement { $$ = new ASTVariableDeclaration(*$1, *$2, *$4);  }
    | array_decl;
    | EXPORT variable_decl { $$ = $2; $$->exporting = true; };

array_decl: composited_type id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTVariableDeclaration(*$1, *$2, *$4); }
	| composited_type id LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET EQUAL LEFT_BRACE init_list RIGHT_BRACE {$$ = new ASTVariableDeclaration(*$1, *$2, *$4, *$8); }
	| composited_type id MUT LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET { $$ = new ASTVariableDeclaration(*$1, *$2, *$5); $$->mut = true; }
	| composited_type id MUT LEFT_SQUARE_BRACKET constant_int RIGHT_SQUARE_BRACKET EQUAL LEFT_BRACE init_list RIGHT_BRACE {$$ = new ASTVariableDeclaration(*$1, *$2, *$5, *$9); $$->mut = true; }

init_list: id_or_constant { $$ = new std::vector<std::unique_ptr<ASTNode>>; auto s = std::unique_ptr<ASTNode>($1); $$->push_back(std::move(s)); }
	| init_list COMMA id_or_constant { auto s = std::unique_ptr<ASTNode>($3);  $1->push_back(std::move(s)); $$ = $1; }

return_statement: RETURN assignable_statement { $$ = new ASTReturnStatement(*$2); };

if_statement: cond_block { $$ = new ASTIfStatement(*$1, NULL); } | cond_block ELSE scope { $$ = new ASTIfStatement(*$1, $3); }

cond_block: IF LEFT_BRACKET assignable_statement RIGHT_BRACKET scope 
    { 
        $$ = new std::vector<std::unique_ptr<ASTConditionalBlock>>();
        auto cb = std::make_unique<ASTConditionalBlock>(*$3, *$5);
        $$->push_back(std::move(cb));
    }
    | cond_block ELSE IF LEFT_BRACKET assignable_statement RIGHT_BRACKET scope
    {
        auto cb = std::make_unique<ASTConditionalBlock>(*$5, *$7);
        $1->push_back(std::move(cb));
    }

while_loop: WHILE LEFT_BRACKET assignable_statement RIGHT_BRACKET scope { $$ = new ASTWhileStatement(*$3, *$5); };

for_loop: FOR LEFT_BRACKET statement SEMICOLON assignable_statement SEMICOLON assignable_statement RIGHT_BRACKET scope
{
 $$ = new ASTForStatement(*$3, *$5, *$7, *$9);
}

struct_list: struct_list struct_pair { auto s = std::unique_ptr<ASTStructMemberDeclaration>($2); $1->args.push_back(std::move(s)); }
    | struct_pair { $$ = new ASTStructMemberDeclarations(); auto s = std::unique_ptr<ASTStructMemberDeclaration>($1); $$->args.push_back(std::move(s)); };

struct_pair: composited_type id SEMICOLON { $$ = new ASTStructMemberDeclaration(*$1, *$2, NULL); }
	| composited_type id EQUAL assignable_statement SEMICOLON { $$ = new ASTStructMemberDeclaration(*$1, *$2, $4); }

arg_list: arg_list COMMA arg_pair { auto s = std::unique_ptr<ASTFunctionArg>($3); $1->args.push_back(std::move(s)); }
    | arg_pair { $$ = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>($1); $$->args.push_back(std::move(s)); };

statement_list: statement_list COMMA assignable_statement { auto s = std::unique_ptr<ASTStatement>($3); $1->push_back(std::move(s)); }
    | assignable_statement { $$ = new std::vector<std::unique_ptr<ASTStatement>>(); auto s = std::unique_ptr<ASTStatement>($1); $$->push_back(std::move(s)); };

func_ptr: FUNC_PTR type type LEFT_BRACKET type_list RIGHT_BRACKET { $$ = new ASTFunctionPointerDefinition(*$2, *$3, *$5); }
	| EXPORT func_ptr { $$ = $2; $$->exporting = true; };

arg_pair: composited_type id { $$ = new ASTFunctionArg(*$1, *$2); } | FSTOP FSTOP FSTOP { $$ = new ASTFunctionArg(); };

enum_def: ENUM type LEFT_BRACE enum_parts RIGHT_BRACE { /*printf("enum_def\n");*/ $$ = new ASTEnumDefinition(*$2, *$4); }
	| EXPORT enum_def { $$ = $2; $$->exporting = true; };

enum_parts: enum_part { $$ = new ASTEnumParts(); auto s = std::unique_ptr<ASTEnumPart>($1); $$->parts.push_back(std::move(s)); }
	| enum_parts COMMA enum_part { auto s = std::unique_ptr<ASTEnumPart>($3); $1->parts.push_back(std::move(s)); }

enum_part: id { $$ = new ASTEnumPart(*$1, nullptr); } | id EQUAL constant_int { /*printf("enum_part\n");*/ $$ = new ASTEnumPart(*$1, $3); }

id_or_constant: id | constant;

include_or_link: INCLUDE STRING  { $$ = new ASTIncludeStatement(yylval.string); } | LINK STRING { $$ = new ASTIncludeStatement(yylval.string); };

constant: constant_int | constant_enum_value | constant_bool | FLOAT { $$ = new ASTConstantFloat(yylval.fl); } | STRING { $$ = new ASTConstantString(yylval.string); } | NULLPTR { $$ = new ASTConstantNullptr(); };

constant_int: INTEGER { $$ = new ASTConstantInt(yylval.integer); };

constant_bool: TRUE { $$ = new ASTConstantInt(1); } | FALSE { $$ = new ASTConstantInt(0); };

constant_enum_value: type COLON COLON id { $$ = new ASTConstantEnumValue(*$1, *$4); };

id: IDENTIFIER { $$ = new ASTIdentifier($1); };

type: TYPE { $$ = new ASTIdentifier($1); };

composited_type: type { $$ = $1;} | MUT composited_type { $$ = $2; $$->identifier.insert(0, "mut "); } | composited_type ASTERISK { $1->identifier.append("*"); } | composited_type MUT { $1->identifier.append(" mut "); } ;

type_list: composited_type { $$ = new std::vector<std::unique_ptr<ASTIdentifier>>(); auto s = std::unique_ptr<ASTIdentifier>($1);  $$->push_back(std::move(s)); }
	| type_list COMMA composited_type { auto s = std::unique_ptr<ASTIdentifier>($3);  $1->push_back(std::move(s)); };

%%