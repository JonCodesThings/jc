/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_GEN_JC_PARSER_HPP_INCLUDED
# define YY_YY_GEN_JC_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    INTEGER = 260,
    FLOAT = 261,
    TYPE = 262,
    LEFT_BRACKET = 263,
    RIGHT_BRACKET = 264,
    LEFT_BRACE = 265,
    RIGHT_BRACE = 266,
    LEFT_SQUARE_BRACKET = 267,
    RIGHT_SQUARE_BRACKET = 268,
    COMMA = 269,
    FSTOP = 270,
    SEMICOLON = 271,
    PLUS = 272,
    MINUS = 273,
    ASTERISK = 274,
    FORWARD_SLASH = 275,
    EQUAL = 276,
    EQUAL_EQUAL = 277,
    EXCLAMATION = 278,
    EXCLAMATION_EQUAL = 279,
    GREATER = 280,
    GREATER_EQUAL = 281,
    LESSER = 282,
    LESSER_EQUAL = 283,
    AND = 284,
    AND_AND = 285,
    OR = 286,
    OR_OR = 287,
    RETURN = 288,
    DEFER = 289,
    IF = 290,
    ELSE = 291,
    FOR = 292,
    WHILE = 293,
    TYPEDEF = 294,
    ALIAS = 295,
    EXTERN = 296,
    IMPORT = 297,
    EXPORT = 298,
    STRUCT = 299,
    ARROW = 300,
    UNKNOWN = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 42 "gen/jc_parser.y" /* yacc.c:1909  */

ASTNode *node;
ASTStatement *statement;
ASTDeferredStatement *defer_statement;
ASTExpression *expression;
ASTFunctionArg *function_arg;
ASTFunctionArgs *function_args;
ASTFunctionCall *function_call;
ASTFunctionDeclaration *function_declaration;
ASTFunctionDefinition *function_definition;
ASTStructDefinition *struct_definition;
ASTMemberOperator *member_operator;
ASTIfStatement *if_statement;
ASTForStatement *for_loop;
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
int integer;
float fl;
int token;

#line 130 "gen/jc_parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GEN_JC_PARSER_HPP_INCLUDED  */
