/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "gen/jc_parser.y"

#include <stdio.h>
#include <math.h>
#include <vector>
#include <include/AST.hpp>

std::unique_ptr<ASTBlock> base;

extern int yylex();
extern int yyparse();
extern int yylineno;
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

/* Line 371 of yacc.c  */
#line 108 "gen/jc_parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "jc_parser.hpp".  */
#ifndef YY_YY_GEN_JC_PARSER_HPP_INCLUDED
# define YY_YY_GEN_JC_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     INCLUDE = 299,
     STRUCT = 300,
     ARROW = 301,
     UNKNOWN = 302
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 42 "gen/jc_parser.y"

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
ASTVariableDeclaration *variable_declaration;
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


/* Line 387 of yacc.c  */
#line 229 "gen/jc_parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_GEN_JC_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 257 "gen/jc_parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  85
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   340

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    15,    17,    20,
      23,    26,    28,    31,    33,    35,    37,    39,    41,    43,
      45,    47,    49,    51,    53,    57,    61,    67,    70,    72,
      74,    76,    78,    80,    82,    84,    86,    88,    92,    95,
      98,   100,   102,   104,   106,   108,   110,   112,   114,   116,
     118,   120,   122,   124,   126,   128,   130,   132,   136,   140,
     144,   148,   152,   157,   161,   165,   168,   171,   176,   181,
     185,   189,   193,   197,   201,   205,   209,   213,   217,   221,
     225,   229,   233,   237,   241,   245,   249,   253,   257,   261,
     268,   274,   277,   283,   290,   294,   297,   301,   306,   309,
     314,   316,   319,   325,   328,   330,   334,   340,   348,   354,
     364,   367,   369,   373,   377,   379,   383,   385,   388,   392,
     394,   396,   399,   401,   403,   405,   407,   409,   411
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    51,    -1,    50,    51,    -1,
      54,    -1,    54,    16,    -1,    53,    -1,    52,    53,    -1,
      54,    16,    -1,    59,    16,    -1,    60,    -1,    58,    16,
      -1,    90,    -1,    85,    -1,    86,    -1,    88,    -1,    66,
      -1,    60,    -1,    55,    -1,    56,    -1,    57,    -1,    63,
      -1,   101,    -1,    40,     7,     7,    -1,    39,     7,     7,
      -1,    45,   105,    10,    95,    11,    -1,    34,    59,    -1,
      87,    -1,    64,    -1,    65,    -1,    67,    -1,   100,    -1,
      91,    -1,    61,    -1,    93,    -1,    94,    -1,    10,    52,
      11,    -1,    10,    11,    -1,    42,   104,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,    82,    -1,    83,    -1,    84,    -1,
      68,    -1,   104,    15,   104,    -1,   104,    46,   104,    -1,
     104,    21,    59,    -1,    74,    21,    59,    -1,    67,    21,
      59,    -1,     8,   105,     9,   100,    -1,   100,    17,    17,
      -1,   100,    18,    18,    -1,    29,   104,    -1,    19,   104,
      -1,   104,    12,   103,    13,    -1,   104,    12,   104,    13,
      -1,   100,    17,   100,    -1,   100,    17,    64,    -1,   100,
      18,   100,    -1,   100,    18,    64,    -1,   100,    19,   100,
      -1,   100,    19,    64,    -1,   100,    20,   100,    -1,   100,
      20,    64,    -1,   100,    22,   100,    -1,   100,    22,    64,
      -1,   100,    24,   100,    -1,   100,    24,    64,    -1,   100,
      27,   100,    -1,   100,    27,    64,    -1,   100,    25,   100,
      -1,   100,    25,    64,    -1,   100,    28,   100,    -1,   100,
      28,    64,    -1,   100,    26,   100,    -1,   100,    26,    64,
      -1,   105,   104,     8,    97,     9,    62,    -1,   105,   104,
       8,     9,    62,    -1,    43,    85,    -1,   105,   104,     8,
       9,    16,    -1,   105,   104,     8,    97,     9,    16,    -1,
      41,    86,    16,    -1,    43,    86,    -1,   104,     8,     9,
      -1,   104,     8,    98,     9,    -1,   105,   104,    -1,   105,
     104,    21,    59,    -1,    89,    -1,    43,    88,    -1,   105,
     104,    12,   103,    13,    -1,    33,    59,    -1,    92,    -1,
      92,    36,    62,    -1,    35,     8,    59,     9,    62,    -1,
      92,    36,    35,     8,    59,     9,    62,    -1,    38,     8,
      59,     9,    62,    -1,    37,     8,    54,    16,    59,    16,
      59,     9,    62,    -1,    95,    96,    -1,    96,    -1,   105,
     104,    16,    -1,    97,    14,    99,    -1,    99,    -1,    98,
      14,    59,    -1,    59,    -1,   105,   104,    -1,    15,    15,
      15,    -1,   104,    -1,   102,    -1,    44,     4,    -1,   103,
      -1,     6,    -1,     4,    -1,     5,    -1,     3,    -1,     7,
      -1,   105,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   135,   135,   137,   138,   140,   140,   142,   143,   145,
     145,   145,   146,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   150,   152,   154,   156,   158,   158,
     158,   158,   158,   160,   160,   162,   162,   164,   164,   166,
     168,   168,   168,   168,   168,   168,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   172,   174,   174,   176,
     177,   178,   180,   182,   184,   186,   188,   190,   191,   193,
     194,   196,   197,   199,   200,   202,   203,   205,   206,   208,
     209,   211,   212,   214,   215,   217,   218,   220,   221,   223,
     224,   225,   227,   228,   229,   230,   232,   233,   235,   236,
     237,   238,   240,   242,   244,   244,   246,   252,   258,   260,
     265,   266,   268,   270,   271,   273,   274,   276,   276,   278,
     278,   280,   282,   282,   282,   284,   286,   288,   288
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "INTEGER",
  "FLOAT", "TYPE", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_BRACE",
  "RIGHT_BRACE", "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET", "COMMA",
  "FSTOP", "SEMICOLON", "PLUS", "MINUS", "ASTERISK", "FORWARD_SLASH",
  "EQUAL", "EQUAL_EQUAL", "EXCLAMATION", "EXCLAMATION_EQUAL", "GREATER",
  "GREATER_EQUAL", "LESSER", "LESSER_EQUAL", "AND", "AND_AND", "OR",
  "OR_OR", "RETURN", "DEFER", "IF", "ELSE", "FOR", "WHILE", "TYPEDEF",
  "ALIAS", "EXTERN", "IMPORT", "EXPORT", "INCLUDE", "STRUCT", "ARROW",
  "UNKNOWN", "$accept", "module", "statements", "node_setup",
  "semicoloned_statements", "semicoloned_statement", "statement",
  "alias_statement", "typedef_statement", "struct_def", "defer_statement",
  "assignable_statement", "flow_control", "loop", "scope", "import",
  "unary_op", "binary_op", "assign_op", "member_op", "variable_assign",
  "cast", "increment", "decrement", "address_of", "dereference",
  "array_index", "add", "subtract", "multiply", "divide", "equality",
  "inequality", "lesser", "greater", "lesser_or_equal", "greater_or_equal",
  "function_def", "function_decl", "function_call", "variable_decl",
  "array_decl", "return_statement", "if_statement", "cond_block",
  "while_loop", "for_loop", "struct_list", "struct_pair", "arg_list",
  "statement_list", "arg_pair", "id_or_constant", "include", "constant",
  "constant_int", "id", "type", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    53,    53,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    56,    57,    58,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    62,    62,    63,
      64,    64,    64,    64,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    67,    67,    68,
      68,    68,    69,    70,    71,    72,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    85,    86,    86,    86,    86,    87,    87,    88,    88,
      88,    88,    89,    90,    91,    91,    92,    92,    93,    94,
      95,    95,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   101,   102,   102,   102,   103,   104,   105,   105
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     1,     2,     2,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     5,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     4,     3,     3,     2,     2,     4,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     6,
       5,     2,     5,     6,     3,     2,     3,     4,     2,     4,
       1,     2,     5,     2,     1,     3,     5,     7,     5,     9,
       2,     1,     3,     3,     1,     3,     1,     2,     3,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   126,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     3,     5,    19,    20,
      21,    18,    34,    22,    17,     0,    56,     0,    14,    15,
      16,   100,    13,    33,   104,    35,    36,    23,     0,     0,
     124,   125,   123,     0,     0,     0,   103,    29,    30,    31,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    28,    32,   120,   122,
     119,     0,     0,     0,     0,     0,     0,     0,     0,    39,
      91,    95,   101,   121,     0,     1,     4,     6,     0,     0,
       0,     0,     0,     0,     0,   128,    98,     0,    66,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    24,    94,     0,     0,    61,
      60,     0,     0,   105,     0,     0,    57,    59,    58,     0,
       0,     0,     0,    63,    70,    69,   119,    64,    72,    71,
      74,    73,    76,    75,    78,    77,    80,    79,    84,    83,
      88,    87,    82,    81,    86,    85,    96,   116,     0,     0,
       0,     0,     0,     0,   111,     0,    38,     0,     0,     7,
       0,     0,     0,    11,    31,    45,   119,     0,    67,    68,
       0,     0,     0,   114,     0,     0,    99,    62,   119,     0,
       0,    97,     0,   106,     0,   108,     0,     0,    26,   110,
       0,    27,    37,     8,     9,    12,    10,     0,    92,    90,
       0,     0,     0,   117,   102,   115,     0,     0,   112,     0,
     118,    93,    89,   113,     0,   107,     0,   109
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    14,    15,    16,   168,   169,    17,    18,    19,    20,
     171,   172,    21,    22,   123,    23,    47,    48,    24,    49,
      26,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    28,    29,    66,
      30,    31,    32,    33,    34,    35,    36,   163,   164,   182,
     158,   183,    67,    37,    68,    69,    70,    39
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
     246,  -155,  -155,   296,     9,    34,    54,    64,    73,    15,
      96,    20,   110,   111,   120,   246,  -155,    -4,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,   100,  -155,   102,  -155,  -155,
    -155,  -155,  -155,  -155,   101,  -155,  -155,  -155,    18,    12,
    -155,  -155,  -155,   111,    96,    96,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,   302,  -155,  -155,
      13,   296,   246,   296,   119,   124,    15,   132,    12,  -155,
    -155,  -155,  -155,  -155,    22,  -155,  -155,  -155,   296,   296,
      -1,    86,    96,   296,    96,  -155,    39,     5,  -155,  -155,
      98,    90,   296,   296,   296,   296,   296,   296,   296,   296,
     289,   140,   134,   142,  -155,  -155,  -155,   144,   111,  -155,
    -155,   190,   145,  -155,   141,   147,  -155,  -155,  -155,    28,
     153,   296,   130,  -155,  -155,    95,   149,  -155,  -155,    95,
    -155,    95,  -155,    95,  -155,    95,  -155,    95,  -155,    95,
    -155,    95,  -155,    95,  -155,    95,  -155,  -155,    31,   152,
     296,   152,    37,    81,  -155,    12,  -155,   296,   233,  -155,
     150,   151,   157,   169,   100,   102,     8,   296,  -155,  -155,
      57,   148,    70,  -155,    12,   155,  -155,  -155,  -155,   170,
     168,  -155,   296,  -155,   172,  -155,   174,    91,  -155,  -155,
     175,  -155,  -155,  -155,  -155,  -155,  -155,   156,  -155,  -155,
     154,    71,    59,  -155,  -155,  -155,   296,   176,  -155,   152,
    -155,  -155,  -155,  -155,   191,  -155,   152,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,  -155,   184,  -155,    36,   -71,  -155,  -155,  -155,
    -155,    -3,  -113,  -155,  -154,  -155,   231,  -155,  -155,     3,
    -155,  -155,  -155,  -155,  -155,  -155,     4,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,  -155,  -155,  -155,   197,     2,  -155,
     199,  -155,  -155,  -155,  -155,  -155,  -155,  -155,    48,    40,
    -155,     0,    75,  -155,  -155,   -81,    38,    -7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -19
static const yytype_int16 yytable[] =
{
      46,   112,    78,    25,    27,   193,    84,   195,   173,   121,
     124,    77,    87,    81,   132,     1,   110,    71,    25,    27,
      91,   110,     2,    92,    95,    91,   209,     2,    92,    93,
      91,    95,   118,    92,   122,     2,    97,   180,    38,    93,
     191,    95,    72,   181,     2,   192,   196,   129,    79,   185,
     170,   130,   181,    38,    94,   173,     9,   222,    76,    94,
     131,     9,    73,    11,    94,   225,     2,   121,   111,    78,
     113,    74,   227,   208,   181,    25,    27,    96,    81,   211,
      75,   121,    98,    99,   212,   119,   120,   221,     2,     1,
     127,    41,   198,     1,    40,    41,    42,   170,    43,     1,
     217,     1,    40,    41,    42,   212,    43,   157,   137,    44,
      38,   165,   189,   190,    83,   133,   117,    44,     2,    45,
      85,    88,   184,    89,   174,   175,   114,    45,   186,   125,
     126,   115,   128,     1,    40,    41,    42,    90,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   116,   159,
     160,   161,   162,   177,   178,   184,   165,   194,    41,   176,
     179,    91,   121,   210,   201,   219,   204,   205,   214,   220,
     188,   174,   175,   206,   207,   135,   139,   141,   143,   145,
     147,   149,   151,   153,   155,   -18,   137,   133,   216,   215,
     208,   218,   221,     1,    40,    41,    42,     2,    43,    86,
     226,   166,   197,   200,   203,   184,   176,   187,    80,    44,
      82,   199,   223,   224,     0,     0,     0,     0,     0,    45,
       0,     0,   213,     3,   167,     4,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     1,    40,    41,    42,
       2,    43,     0,     0,   202,     0,     0,     0,     0,     1,
       0,     0,    44,     2,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     0,     3,   167,     4,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     3,
       0,     4,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     1,    40,    41,    42,     0,    43,   156,     1,
      40,    41,    42,     0,    43,     0,     0,     0,    44,     0,
       0,     0,     0,     0,     0,    44,     0,     0,    45,   100,
     101,   102,   103,     0,   104,    45,   105,   106,   107,   108,
     109,   134,   138,   140,   142,   144,   146,   148,   150,   152,
     154
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-155)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    72,     9,     0,     0,   159,    13,   161,   121,    10,
      91,     9,    16,    11,     9,     3,     8,     8,    15,    15,
      12,     8,     7,    15,    19,    12,   180,     7,    15,    21,
      12,    19,    10,    15,    35,     7,    43,     9,     0,    21,
       9,    19,     8,    15,     7,    14,     9,     8,    10,   130,
     121,    12,    15,    15,    46,   168,    41,   211,    43,    46,
      21,    41,     8,    43,    46,   219,     7,    10,    71,    76,
      73,     7,   226,    16,    15,    72,    72,    39,    76,     9,
       7,    10,    44,    45,    14,    88,    89,    16,     7,     3,
      93,     5,    11,     3,     4,     5,     6,   168,     8,     3,
       9,     3,     4,     5,     6,    14,     8,   110,    18,    19,
      72,   118,    17,    18,     4,    17,    78,    19,     7,    29,
       0,    21,   129,    21,   121,   121,     7,    29,   131,    91,
      92,     7,    94,     3,     4,     5,     6,    36,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    16,     9,
      16,     9,     8,     8,    13,   162,   163,   160,     5,   121,
      13,    12,    10,    15,   167,     9,    16,    16,    13,    15,
     132,   168,   168,    16,   177,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    16,    18,    17,    16,   192,
      16,    16,    16,     3,     4,     5,     6,     7,     8,    15,
       9,    11,   162,   165,   168,   212,   168,   132,    11,    19,
      11,   163,   212,   216,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,   184,    33,    34,    35,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    19,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    33,    34,    35,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    33,
      -1,    35,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     3,     4,     5,     6,    -1,     8,     9,     3,
       4,     5,     6,    -1,     8,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    29,    17,
      18,    19,    20,    -1,    22,    29,    24,    25,    26,    27,
      28,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,    33,    35,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    49,    50,    51,    54,    55,    56,
      57,    60,    61,    63,    66,    67,    68,    74,    85,    86,
      88,    89,    90,    91,    92,    93,    94,   101,   104,   105,
       4,     5,     6,     8,    19,    29,    59,    64,    65,    67,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    87,   100,   102,   103,
     104,     8,     8,     8,     7,     7,    43,    86,   105,   104,
      85,    86,    88,     4,   105,     0,    51,    16,    21,    21,
      36,    12,    15,    21,    46,    19,   104,   105,   104,   104,
      17,    18,    19,    20,    22,    24,    25,    26,    27,    28,
       8,    59,    54,    59,     7,     7,    16,   104,    10,    59,
      59,    10,    35,    62,   103,   104,   104,    59,   104,     8,
      12,    21,     9,    17,    64,   100,   104,    18,    64,   100,
      64,   100,    64,   100,    64,   100,    64,   100,    64,   100,
      64,   100,    64,   100,    64,   100,     9,    59,    98,     9,
      16,     9,     8,    95,    96,   105,    11,    34,    52,    53,
      54,    58,    59,    60,    67,    74,   104,     8,    13,    13,
       9,    15,    97,    99,   105,   103,    59,   100,   104,    17,
      18,     9,    14,    62,    59,    62,     9,    97,    11,    96,
     104,    59,    11,    53,    16,    16,    16,    59,    16,    62,
      15,     9,    14,   104,    13,    59,    16,     9,    16,     9,
      15,    16,    62,    99,    59,    62,     9,    62
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 135 "gen/jc_parser.y"
    { base = std::make_unique<ASTBlock>(); std::unique_ptr<ASTBlock> b = std::unique_ptr<ASTBlock>((yyvsp[(1) - (1)].scope_block)); base->block->push_back(std::move(b)); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 137 "gen/jc_parser.y"
    { (yyval.scope_block) = new ASTBlock(); auto s = std::unique_ptr<ASTStatement>((yyvsp[(1) - (1)].statement)); (yyval.scope_block)->block->push_back(std::move(s)); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 138 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTStatement>((yyvsp[(2) - (2)].statement)); (yyvsp[(1) - (2)].scope_block)->block->push_back(std::move(s)); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 140 "gen/jc_parser.y"
    { SetNodeInfo(*(yyval.statement)); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 140 "gen/jc_parser.y"
    { SetNodeInfo(*(yyval.statement)); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 142 "gen/jc_parser.y"
    { (yyval.scope_block) = new ASTBlock(); auto statement = std::unique_ptr<ASTStatement>((yyvsp[(1) - (1)].statement)); (yyval.scope_block)->block->push_back(std::move(statement)); SetNodeInfo(*(yyval.scope_block)); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 143 "gen/jc_parser.y"
    { auto statement = std::unique_ptr<ASTStatement>((yyvsp[(2) - (2)].statement)); (yyvsp[(1) - (2)].scope_block)->block->push_back(std::move(statement)); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 145 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (2)].statement)); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 145 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (2)].statement)); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 145 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (1)].statement)); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 146 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (2)].defer_statement)); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 150 "gen/jc_parser.y"
    { (yyval.type_mod) = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::ALIAS); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 152 "gen/jc_parser.y"
    { (yyval.type_mod) = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::TYPEDEF); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 154 "gen/jc_parser.y"
    { (yyval.statement) = new ASTStructDefinition(*(yyvsp[(2) - (5)].id), *(yyvsp[(4) - (5)].function_args)); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 156 "gen/jc_parser.y"
    { (yyval.defer_statement) = new ASTDeferredStatement(*(yyvsp[(2) - (2)].statement)); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 164 "gen/jc_parser.y"
    { (yyval.scope_block) = (yyvsp[(2) - (3)].scope_block); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 164 "gen/jc_parser.y"
    { (yyval.scope_block) = new ASTBlock(); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 166 "gen/jc_parser.y"
    { (yyval.statement) = new ASTImportStatement(); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 174 "gen/jc_parser.y"
    { (yyval.statement) = new ASTMemberOperator(*(yyvsp[(1) - (3)].id), *(yyvsp[(3) - (3)].id), ASTMemberOperator::OP::DOT); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 174 "gen/jc_parser.y"
    { (yyval.statement) = new ASTMemberOperator(*(yyvsp[(1) - (3)].id), *(yyvsp[(3) - (3)].id), ASTMemberOperator::OP::ARROW); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 176 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[(1) - (3)].id), *(yyvsp[(3) - (3)].statement));  }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 177 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[(1) - (3)].unary_operator), *(yyvsp[(3) - (3)].statement)); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 178 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[(1) - (3)].statement), *(yyvsp[(3) - (3)].statement)); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 180 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(4) - (4)].node), (yyvsp[(2) - (4)].id), ASTUnaryOperator::CAST); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 182 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (3)].node), ASTUnaryOperator::INCREMENT);  }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 184 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (3)].node), ASTUnaryOperator::DECREMENT);  }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 186 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(2) - (2)].id), ASTUnaryOperator::ADDRESS_OF); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 188 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(2) - (2)].id), ASTUnaryOperator::DEREFERENCE); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 190 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (4)].id), *(yyvsp[(3) - (4)].constant_int), ASTUnaryOperator::ARRAY_INDEX); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 191 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].id), ASTUnaryOperator::ARRAY_INDEX);}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 193 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::ADD);  }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 194 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::ADD); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 196 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::SUBTRACT);  }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 197 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::SUBTRACT); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 199 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::MULTIPLY);  }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 200 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::MULTIPLY); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 202 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::DIVIDE);  }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 203 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::DIVIDE); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 205 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::EQUALITY);  }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 206 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::EQUALITY); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 208 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::INEQUALITY);  }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 209 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::INEQUALITY); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 211 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::LESSER);  }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 212 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::LESSER); }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 214 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::GREATER);  }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 215 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::GREATER); }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 217 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::LESSER_OR_EQUAL);  }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 218 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::LESSER_OR_EQUAL); }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 220 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::GREATER_OR_EQUAL);  }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 221 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::GREATER_OR_EQUAL); }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 223 "gen/jc_parser.y"
    {  (yyval.function_definition) = new ASTFunctionDefinition(*(yyvsp[(1) - (6)].id), *(yyvsp[(2) - (6)].id), *(yyvsp[(4) - (6)].function_args), *(yyvsp[(6) - (6)].scope_block));  }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 224 "gen/jc_parser.y"
    {  (yyval.function_definition) = new ASTFunctionDefinition(*(yyvsp[(1) - (5)].id), *(yyvsp[(2) - (5)].id), *new ASTFunctionArgs(), *(yyvsp[(5) - (5)].scope_block));  }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 225 "gen/jc_parser.y"
    { (yyval.function_definition) = (yyvsp[(2) - (2)].function_definition); (yyval.function_definition)->SetExporting(true); }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 227 "gen/jc_parser.y"
    { (yyval.function_declaration) = new ASTFunctionDeclaration(*(yyvsp[(1) - (5)].id), *(yyvsp[(2) - (5)].id), *new ASTFunctionArgs());  }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 228 "gen/jc_parser.y"
    { (yyval.function_declaration) = new ASTFunctionDeclaration(*(yyvsp[(1) - (6)].id), *(yyvsp[(2) - (6)].id), *(yyvsp[(4) - (6)].function_args));  }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 230 "gen/jc_parser.y"
    { (yyval.function_declaration) = (yyvsp[(2) - (2)].function_declaration); (yyval.function_declaration)->SetExporting(true); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 232 "gen/jc_parser.y"
    { (yyval.function_call) = new ASTFunctionCall(*(yyvsp[(1) - (3)].id)); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 233 "gen/jc_parser.y"
    { (yyval.function_call) = new ASTFunctionCall(*(yyvsp[(1) - (4)].id), *(yyvsp[(3) - (4)].statement_list)); }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 235 "gen/jc_parser.y"
    { (yyval.variable_declaration) = new ASTVariableDeclaration(*(yyvsp[(1) - (2)].id), *(yyvsp[(2) - (2)].id));  }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 236 "gen/jc_parser.y"
    { (yyval.variable_declaration) = new ASTVariableDeclaration(*(yyvsp[(1) - (4)].id), *(yyvsp[(2) - (4)].id), *(yyvsp[(4) - (4)].statement));  }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 238 "gen/jc_parser.y"
    { (yyval.variable_declaration) = (yyvsp[(2) - (2)].variable_declaration); (yyval.variable_declaration)->exporting = true; }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 240 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[(1) - (5)].id), *(yyvsp[(2) - (5)].id), *(yyvsp[(4) - (5)].constant_int)); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 242 "gen/jc_parser.y"
    { (yyval.statement) = new ASTReturnStatement(*(yyvsp[(2) - (2)].statement)); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 244 "gen/jc_parser.y"
    { (yyval.if_statement) = new ASTIfStatement(*(yyvsp[(1) - (1)].cond_block), NULL); }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 244 "gen/jc_parser.y"
    { (yyval.if_statement) = new ASTIfStatement(*(yyvsp[(1) - (3)].cond_block), (yyvsp[(3) - (3)].scope_block)); }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 247 "gen/jc_parser.y"
    { 
        (yyval.cond_block) = new std::vector<std::unique_ptr<ASTConditionalBlock>>();
        auto cb = std::make_unique<ASTConditionalBlock>(*(yyvsp[(3) - (5)].statement), *(yyvsp[(5) - (5)].scope_block));
        (yyval.cond_block)->push_back(std::move(cb));
    }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 253 "gen/jc_parser.y"
    {
        auto cb = std::make_unique<ASTConditionalBlock>(*(yyvsp[(5) - (7)].statement), *(yyvsp[(7) - (7)].scope_block));
        (yyvsp[(1) - (7)].cond_block)->push_back(std::move(cb));
    }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 258 "gen/jc_parser.y"
    { (yyval.while_loop) = new ASTWhileStatement(*(yyvsp[(3) - (5)].statement), *(yyvsp[(5) - (5)].scope_block)); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 261 "gen/jc_parser.y"
    {
 (yyval.for_loop) = new ASTForStatement(*(yyvsp[(3) - (9)].statement), *(yyvsp[(5) - (9)].statement), *(yyvsp[(7) - (9)].statement), *(yyvsp[(9) - (9)].scope_block));
}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 265 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(2) - (2)].function_arg)); (yyvsp[(1) - (2)].function_args)->args.push_back(std::move(s)); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 266 "gen/jc_parser.y"
    { (yyval.function_args) = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(1) - (1)].function_arg)); (yyval.function_args)->args.push_back(std::move(s)); }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 268 "gen/jc_parser.y"
    { (yyval.function_arg) = new ASTFunctionArg(*(yyvsp[(1) - (3)].id), *(yyvsp[(2) - (3)].id)); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 270 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(3) - (3)].function_arg)); (yyvsp[(1) - (3)].function_args)->args.push_back(std::move(s)); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 271 "gen/jc_parser.y"
    { (yyval.function_args) = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(1) - (1)].function_arg)); (yyval.function_args)->args.push_back(std::move(s)); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 273 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTStatement>((yyvsp[(3) - (3)].statement)); (yyvsp[(1) - (3)].statement_list)->push_back(std::move(s)); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 274 "gen/jc_parser.y"
    { (yyval.statement_list) = new std::vector<std::unique_ptr<ASTStatement>>(); auto s = std::unique_ptr<ASTStatement>((yyvsp[(1) - (1)].statement)); (yyval.statement_list)->push_back(std::move(s)); }
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 276 "gen/jc_parser.y"
    { (yyval.function_arg) = new ASTFunctionArg(*(yyvsp[(1) - (2)].id), *(yyvsp[(2) - (2)].id)); }
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 276 "gen/jc_parser.y"
    { (yyval.function_arg) = new ASTFunctionArg(); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 280 "gen/jc_parser.y"
    { (yyval.statement) = new ASTIncludeStatement(yylval.string); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 282 "gen/jc_parser.y"
    { (yyval.constant) = new ASTConstantFloat(yylval.fl); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 282 "gen/jc_parser.y"
    { (yyval.constant) = new ASTConstantString(yylval.string); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 284 "gen/jc_parser.y"
    { (yyval.constant_int) = new ASTConstantInt(yylval.integer); }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 286 "gen/jc_parser.y"
    { (yyval.id) = new ASTIdentifier((yyvsp[(1) - (1)].string)); }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 288 "gen/jc_parser.y"
    { (yyval.id) = new ASTIdentifier((yyvsp[(1) - (1)].string)); }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 288 "gen/jc_parser.y"
    { (yyvsp[(1) - (2)].id)->identifier.append("*");  }
    break;


/* Line 1792 of yacc.c  */
#line 2212 "gen/jc_parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 290 "gen/jc_parser.y"

