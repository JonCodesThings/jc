/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_TYPE_GEN_JC_TYPE_PARSER_HPP_INCLUDED
# define YY_TYPE_GEN_JC_TYPE_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef TYPE_DEBUG
# if defined YYDEBUG
#  if YYDEBUG
#   define TYPE_DEBUG 1
#  else
#   define TYPE_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define TYPE_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined TYPE_DEBUG */
#if TYPE_DEBUG
extern int type_debug;
#endif

/* Tokens.  */
#ifndef TYPE_TOKENTYPE
# define TYPE_TOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum type_tokentype {
     STRUCT_TYPE_KEYWORD = 258,
     ALIAS_TYPE_KEYWORD = 259,
     TYPEDEF_TYPE_KEYWORD = 260,
     SEMICOLON_TYPE_KEYWORD = 261,
     IDENTIFIER_TYPE_KEYWORD = 262,
     LB = 263,
     NONE = 264
   };
#endif


#if ! defined TYPE_STYPE && ! defined TYPE_STYPE_IS_DECLARED
typedef union TYPE_STYPE
{
/* Line 2058 of yacc.c  */
#line 19 "gen/jc_type_parser.y"

const char *string;


/* Line 2058 of yacc.c  */
#line 79 "gen/jc_type_parser.hpp"
} TYPE_STYPE;
# define TYPE_STYPE_IS_TRIVIAL 1
# define type_stype TYPE_STYPE /* obsolescent; will be withdrawn */
# define TYPE_STYPE_IS_DECLARED 1
#endif

extern TYPE_STYPE type_lval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int type_parse (void *YYPARSE_PARAM);
#else
int type_parse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int type_parse (void);
#else
int type_parse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_TYPE_GEN_JC_TYPE_PARSER_HPP_INCLUDED  */
