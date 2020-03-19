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
     STRUCT = 299,
     ARROW = 300,
     UNKNOWN = 301
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
#line 227 "gen/jc_parser.cpp"
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
#line 255 "gen/jc_parser.cpp"

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
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  226

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    15,    17,    20,
      23,    26,    28,    31,    33,    35,    37,    39,    41,    43,
      45,    47,    49,    51,    55,    59,    65,    68,    70,    72,
      74,    76,    78,    80,    82,    84,    86,    90,    93,    96,
      98,   100,   102,   104,   106,   108,   110,   112,   114,   116,
     118,   120,   122,   124,   126,   128,   130,   134,   138,   142,
     146,   150,   155,   159,   163,   166,   169,   174,   179,   183,
     187,   191,   195,   199,   203,   207,   211,   215,   219,   223,
     227,   231,   235,   239,   243,   247,   251,   255,   259,   266,
     272,   275,   281,   288,   292,   295,   299,   304,   307,   312,
     314,   320,   323,   325,   329,   335,   343,   349,   359,   362,
     364,   368,   372,   374,   378,   380,   383,   387,   389,   391,
     393,   395,   397,   399,   401,   403
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    -1,    50,    -1,    49,    50,    -1,
      53,    -1,    53,    16,    -1,    52,    -1,    51,    52,    -1,
      53,    16,    -1,    58,    16,    -1,    59,    -1,    57,    16,
      -1,    89,    -1,    84,    -1,    85,    -1,    87,    -1,    65,
      -1,    59,    -1,    54,    -1,    55,    -1,    56,    -1,    62,
      -1,    40,     7,     7,    -1,    39,     7,     7,    -1,    44,
     103,    10,    94,    11,    -1,    34,    58,    -1,    86,    -1,
      63,    -1,    64,    -1,    66,    -1,    99,    -1,    90,    -1,
      60,    -1,    92,    -1,    93,    -1,    10,    51,    11,    -1,
      10,    11,    -1,    42,   102,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,    82,    -1,    83,    -1,    67,    -1,
     102,    15,   102,    -1,   102,    45,   102,    -1,   102,    21,
      58,    -1,    73,    21,    58,    -1,    66,    21,    58,    -1,
       8,   103,     9,    99,    -1,    99,    17,    17,    -1,    99,
      18,    18,    -1,    29,   102,    -1,    19,   102,    -1,   102,
      12,   101,    13,    -1,   102,    12,   102,    13,    -1,    99,
      17,    99,    -1,    99,    17,    63,    -1,    99,    18,    99,
      -1,    99,    18,    63,    -1,    99,    19,    99,    -1,    99,
      19,    63,    -1,    99,    20,    99,    -1,    99,    20,    63,
      -1,    99,    22,    99,    -1,    99,    22,    63,    -1,    99,
      24,    99,    -1,    99,    24,    63,    -1,    99,    27,    99,
      -1,    99,    27,    63,    -1,    99,    25,    99,    -1,    99,
      25,    63,    -1,    99,    28,    99,    -1,    99,    28,    63,
      -1,    99,    26,    99,    -1,    99,    26,    63,    -1,   103,
     102,     8,    96,     9,    61,    -1,   103,   102,     8,     9,
      61,    -1,    43,    84,    -1,   103,   102,     8,     9,    16,
      -1,   103,   102,     8,    96,     9,    16,    -1,    41,    85,
      16,    -1,    43,    85,    -1,   102,     8,     9,    -1,   102,
       8,    97,     9,    -1,   103,   102,    -1,   103,   102,    21,
      58,    -1,    88,    -1,   103,   102,    12,   101,    13,    -1,
      33,    58,    -1,    91,    -1,    91,    36,    61,    -1,    35,
       8,    58,     9,    61,    -1,    91,    36,    35,     8,    58,
       9,    61,    -1,    38,     8,    58,     9,    61,    -1,    37,
       8,    53,    16,    58,    16,    58,     9,    61,    -1,    94,
      95,    -1,    95,    -1,   103,   102,    16,    -1,    96,    14,
      98,    -1,    98,    -1,    97,    14,    58,    -1,    58,    -1,
     103,   102,    -1,    15,    15,    15,    -1,   102,    -1,   100,
      -1,   101,    -1,     6,    -1,     4,    -1,     5,    -1,     3,
      -1,     7,    -1,   103,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   135,   136,   138,   138,   140,   141,   143,
     143,   143,   144,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   148,   150,   152,   154,   156,   156,   156,
     156,   156,   158,   158,   160,   160,   162,   162,   164,   166,
     166,   166,   166,   166,   166,   168,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   170,   172,   172,   174,   175,
     176,   178,   180,   182,   184,   186,   188,   189,   191,   192,
     194,   195,   197,   198,   200,   201,   203,   204,   206,   207,
     209,   210,   212,   213,   215,   216,   218,   219,   221,   222,
     223,   225,   226,   227,   228,   230,   231,   233,   234,   235,
     237,   239,   241,   241,   243,   249,   255,   257,   262,   263,
     265,   267,   268,   270,   271,   273,   273,   275,   275,   277,
     277,   277,   279,   281,   283,   283
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
  "ALIAS", "EXTERN", "IMPORT", "EXPORT", "STRUCT", "ARROW", "UNKNOWN",
  "$accept", "module", "statements", "node_setup",
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
  "statement_list", "arg_pair", "id_or_constant", "constant",
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
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    55,    56,    57,    58,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    63,
      63,    63,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    66,    66,    67,    67,
      67,    68,    69,    70,    71,    72,    73,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    78,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    85,    85,    85,    85,    86,    86,    87,    87,    87,
      88,    89,    90,    90,    91,    91,    92,    93,    94,    94,
      95,    96,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   100,   101,   102,   103,   103
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     1,     2,     2,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     5,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     4,     3,     3,     2,     2,     4,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     5,
       2,     5,     6,     3,     2,     3,     4,     2,     4,     1,
       5,     2,     1,     3,     5,     7,     5,     9,     2,     1,
       3,     3,     1,     3,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     3,     5,    19,    20,    21,
      18,    33,    22,    17,     0,    55,     0,    14,    15,    16,
      99,    13,    32,   102,    34,    35,     0,     0,   121,   122,
     120,     0,     0,     0,   101,    28,    29,    30,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    27,    31,   118,   119,   117,     0,
       0,     0,     0,     0,     0,     0,     0,    38,    90,    94,
       0,     0,     1,     4,     6,     0,     0,     0,     0,     0,
       0,     0,   125,    97,     0,    65,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    23,    93,     0,     0,     0,    60,    59,     0,
       0,   103,     0,     0,    56,    58,    57,     0,     0,     0,
       0,    62,    69,    68,   117,    63,    71,    70,    73,    72,
      75,    74,    77,    76,    79,    78,    83,    82,    87,    86,
      81,    80,    85,    84,    95,   114,     0,     0,     0,     0,
       0,     0,   109,     0,    37,     0,     0,     7,     0,     0,
       0,    11,    30,    44,   117,     0,    66,    67,     0,     0,
       0,   112,     0,     0,    98,    61,   117,     0,     0,    96,
       0,   104,     0,   106,     0,     0,    25,   108,     0,    26,
      36,     8,     9,    12,    10,     0,    91,    89,     0,     0,
       0,   115,   100,   113,     0,     0,   110,     0,   116,    92,
      88,   111,     0,   105,     0,   107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,   166,   167,    16,    17,    18,    19,
     169,   170,    20,    21,   121,    22,    45,    46,    23,    47,
      25,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    27,    28,    64,
      29,    30,    31,    32,    33,    34,    35,   161,   162,   180,
     156,   181,    65,    66,    67,    68,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -148
static const yytype_int16 yypact[] =
{
      92,  -148,  -148,   279,     5,    13,    15,    19,    78,     4,
      36,    22,    95,    71,    92,  -148,    59,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,    93,  -148,   100,  -148,  -148,  -148,
    -148,  -148,  -148,   112,  -148,  -148,    34,    11,  -148,  -148,
    -148,    95,    36,    36,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,   275,  -148,  -148,    12,   279,
      92,   279,   105,   117,     4,   133,    11,  -148,  -148,  -148,
      11,     6,  -148,  -148,  -148,   279,   279,    23,    98,    36,
     279,    36,  -148,    48,    35,  -148,  -148,    88,   139,   279,
     279,   279,   279,   279,   279,   279,   279,    32,   141,   143,
     142,  -148,  -148,  -148,   155,   162,    95,  -148,  -148,   185,
     163,  -148,   147,   170,  -148,  -148,  -148,    91,   180,   279,
     135,  -148,  -148,    25,   174,  -148,  -148,    25,  -148,    25,
    -148,    25,  -148,    25,  -148,    25,  -148,    25,  -148,    25,
    -148,    25,  -148,    25,  -148,  -148,    50,   184,   279,   184,
     101,   104,  -148,    11,  -148,   279,   227,  -148,   181,   182,
     183,   186,    93,   100,     7,   279,  -148,  -148,    64,   190,
     114,  -148,    11,   187,  -148,  -148,  -148,   191,   189,  -148,
     279,  -148,   193,  -148,   194,   152,  -148,  -148,   196,  -148,
    -148,  -148,  -148,  -148,  -148,   192,  -148,  -148,   198,    68,
      74,  -148,  -148,  -148,   279,   199,  -148,   184,  -148,  -148,
    -148,  -148,   207,  -148,   184,  -148
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,  -148,   203,  -148,    55,   -69,  -148,  -148,  -148,
    -148,    -3,  -113,  -148,  -147,  -148,   212,  -148,  -148,     3,
    -148,  -148,  -148,  -148,  -148,  -148,    18,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,   225,    -2,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,    79,    77,
    -148,    31,   175,  -148,   -80,    76,    -7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -19
static const yytype_int16 yytable[] =
{
      44,   109,    76,    24,    80,    81,   171,    75,   122,    79,
     191,     2,   193,    69,     1,   107,   116,    24,    26,    88,
     107,    70,    89,    71,    88,    92,    72,    89,    90,     2,
      92,   207,    26,   119,    94,     1,    38,    39,    40,     1,
      41,   154,   187,   188,   130,     9,    88,    74,   183,    89,
     168,    42,    91,   171,    92,    90,   127,    91,   120,   189,
     128,    43,   220,     9,   190,    11,   108,    76,   110,   129,
     223,    82,    79,    24,   119,    84,    36,   225,   119,    91,
     206,     2,   117,   118,   219,    73,    77,   125,    26,   179,
      36,     1,    38,    39,    40,     1,    41,   168,     2,     2,
     178,     1,     2,    39,   155,   131,   179,    42,     2,   163,
     194,     2,   111,    93,    85,   196,   179,    43,    95,    96,
     182,    86,   172,   209,   112,     3,   184,     4,   210,     5,
       6,     7,     8,     9,    10,    11,    12,   173,     1,    38,
      39,    40,     1,    38,    39,    40,    36,    41,    87,   113,
     157,   159,   114,   182,   163,   192,   115,   135,    42,   158,
     176,   215,   199,   160,   123,   124,   210,   126,    43,   172,
     127,   175,   205,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   177,   173,    39,    88,   213,     1,    38,
      39,    40,     2,    41,   119,   174,   164,   202,   203,   204,
     212,   217,   -18,   182,    42,   208,   186,   135,   131,   214,
     206,   222,   216,   218,    43,   219,   224,    83,     3,   165,
       4,   201,     5,     6,     7,     8,     9,    10,    11,    12,
       1,    38,    39,    40,     2,    41,    78,   195,   200,   198,
     197,   221,   174,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,     0,   211,     0,
       3,   165,     4,     0,     5,     6,     7,     8,     9,    10,
      11,    12,   133,   137,   139,   141,   143,   145,   147,   149,
     151,   153,     1,    38,    39,    40,     0,    41,     0,     0,
       0,     0,    97,    98,    99,   100,     0,   101,    42,   102,
     103,   104,   105,   106,     0,   185,     0,     0,    43,   132,
     136,   138,   140,   142,   144,   146,   148,   150,   152
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-148)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    70,     9,     0,    11,    12,   119,     9,    88,    11,
     157,     7,   159,     8,     3,     8,    10,    14,     0,    12,
       8,     8,    15,     8,    12,    19,     7,    15,    21,     7,
      19,   178,    14,    10,    41,     3,     4,     5,     6,     3,
       8,     9,    17,    18,     9,    41,    12,    43,   128,    15,
     119,    19,    45,   166,    19,    21,     8,    45,    35,     9,
      12,    29,   209,    41,    14,    43,    69,    74,    71,    21,
     217,     0,    74,    70,    10,    16,     0,   224,    10,    45,
      16,     7,    85,    86,    16,     7,    10,    90,    70,    15,
      14,     3,     4,     5,     6,     3,     8,   166,     7,     7,
       9,     3,     7,     5,   107,    17,    15,    19,     7,   116,
       9,     7,     7,    37,    21,    11,    15,    29,    42,    43,
     127,    21,   119,     9,     7,    33,   129,    35,    14,    37,
      38,    39,    40,    41,    42,    43,    44,   119,     3,     4,
       5,     6,     3,     4,     5,     6,    70,     8,    36,    16,
       9,     9,    76,   160,   161,   158,    80,    18,    19,    16,
      13,     9,   165,     8,    88,    89,    14,    91,    29,   166,
       8,     8,   175,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    13,   166,     5,    12,   190,     3,     4,
       5,     6,     7,     8,    10,   119,    11,    16,    16,    16,
      13,     9,    16,   210,    19,    15,   130,    18,    17,    16,
      16,   214,    16,    15,    29,    16,     9,    14,    33,    34,
      35,   166,    37,    38,    39,    40,    41,    42,    43,    44,
       3,     4,     5,     6,     7,     8,    11,   160,    11,   163,
     161,   210,   166,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,   182,    -1,
      33,    34,    35,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    -1,    22,    19,    24,
      25,    26,    27,    28,    -1,   130,    -1,    -1,    29,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,    33,    35,    37,    38,    39,    40,    41,
      42,    43,    44,    48,    49,    50,    53,    54,    55,    56,
      59,    60,    62,    65,    66,    67,    73,    84,    85,    87,
      88,    89,    90,    91,    92,    93,   102,   103,     4,     5,
       6,     8,    19,    29,    58,    63,    64,    66,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    86,    99,   100,   101,   102,     8,
       8,     8,     7,     7,    43,    85,   103,   102,    84,    85,
     103,   103,     0,    50,    16,    21,    21,    36,    12,    15,
      21,    45,    19,   102,   103,   102,   102,    17,    18,    19,
      20,    22,    24,    25,    26,    27,    28,     8,    58,    53,
      58,     7,     7,    16,   102,   102,    10,    58,    58,    10,
      35,    61,   101,   102,   102,    58,   102,     8,    12,    21,
       9,    17,    63,    99,   102,    18,    63,    99,    63,    99,
      63,    99,    63,    99,    63,    99,    63,    99,    63,    99,
      63,    99,    63,    99,     9,    58,    97,     9,    16,     9,
       8,    94,    95,   103,    11,    34,    51,    52,    53,    57,
      58,    59,    66,    73,   102,     8,    13,    13,     9,    15,
      96,    98,   103,   101,    58,    99,   102,    17,    18,     9,
      14,    61,    58,    61,     9,    96,    11,    95,   102,    58,
      11,    52,    16,    16,    16,    58,    16,    61,    15,     9,
      14,   102,    13,    58,    16,     9,    16,     9,    15,    16,
      61,    98,    58,    61,     9,    61
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
#line 133 "gen/jc_parser.y"
    { base = std::make_unique<ASTBlock>(); std::unique_ptr<ASTBlock> b = std::unique_ptr<ASTBlock>((yyvsp[(1) - (1)].scope_block)); base->block->push_back(std::move(b)); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 135 "gen/jc_parser.y"
    { (yyval.scope_block) = new ASTBlock(); auto s = std::unique_ptr<ASTStatement>((yyvsp[(1) - (1)].statement)); (yyval.scope_block)->block->push_back(std::move(s)); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 136 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTStatement>((yyvsp[(2) - (2)].statement)); (yyvsp[(1) - (2)].scope_block)->block->push_back(std::move(s)); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 138 "gen/jc_parser.y"
    { SetNodeInfo(*(yyval.statement)); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 138 "gen/jc_parser.y"
    { SetNodeInfo(*(yyval.statement)); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 140 "gen/jc_parser.y"
    { (yyval.scope_block) = new ASTBlock(); auto statement = std::unique_ptr<ASTStatement>((yyvsp[(1) - (1)].statement)); (yyval.scope_block)->block->push_back(std::move(statement)); SetNodeInfo(*(yyval.scope_block)); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 141 "gen/jc_parser.y"
    { auto statement = std::unique_ptr<ASTStatement>((yyvsp[(2) - (2)].statement)); (yyvsp[(1) - (2)].scope_block)->block->push_back(std::move(statement)); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 143 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (2)].statement)); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 143 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (2)].statement)); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 143 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (1)].statement)); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 144 "gen/jc_parser.y"
    { SetNodeInfo(*(yyvsp[(1) - (2)].defer_statement)); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 148 "gen/jc_parser.y"
    { (yyval.type_mod) = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::ALIAS); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 150 "gen/jc_parser.y"
    { (yyval.type_mod) = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::TYPEDEF); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 152 "gen/jc_parser.y"
    { (yyval.statement) = new ASTStructDefinition(*(yyvsp[(2) - (5)].id), *(yyvsp[(4) - (5)].function_args)); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 154 "gen/jc_parser.y"
    { (yyval.defer_statement) = new ASTDeferredStatement(*(yyvsp[(2) - (2)].statement)); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 162 "gen/jc_parser.y"
    { (yyval.scope_block) = (yyvsp[(2) - (3)].scope_block); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 162 "gen/jc_parser.y"
    { (yyval.scope_block) = new ASTBlock(); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 164 "gen/jc_parser.y"
    { (yyval.statement) = new ASTImportStatement(); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 172 "gen/jc_parser.y"
    { (yyval.statement) = new ASTMemberOperator(*(yyvsp[(1) - (3)].id), *(yyvsp[(3) - (3)].id), ASTMemberOperator::OP::DOT); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 172 "gen/jc_parser.y"
    { (yyval.statement) = new ASTMemberOperator(*(yyvsp[(1) - (3)].id), *(yyvsp[(3) - (3)].id), ASTMemberOperator::OP::ARROW); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 174 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[(1) - (3)].id), *(yyvsp[(3) - (3)].statement));  }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 175 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[(1) - (3)].unary_operator), *(yyvsp[(3) - (3)].statement)); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 176 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[(1) - (3)].statement), *(yyvsp[(3) - (3)].statement)); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 178 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(4) - (4)].node), (yyvsp[(2) - (4)].id), ASTUnaryOperator::CAST); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 180 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (3)].node), ASTUnaryOperator::INCREMENT);  }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 182 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (3)].node), ASTUnaryOperator::DECREMENT);  }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 184 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(2) - (2)].id), ASTUnaryOperator::ADDRESS_OF); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 186 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(2) - (2)].id), ASTUnaryOperator::DEREFERENCE); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 188 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (4)].id), *(yyvsp[(3) - (4)].constant_int), ASTUnaryOperator::ARRAY_INDEX); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 189 "gen/jc_parser.y"
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].id), ASTUnaryOperator::ARRAY_INDEX);}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 191 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::ADD);  }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 192 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::ADD); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 194 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::SUBTRACT);  }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 195 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::SUBTRACT); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 197 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::MULTIPLY);  }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 198 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::MULTIPLY); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 200 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::DIVIDE);  }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 201 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::DIVIDE); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 203 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::EQUALITY);  }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 204 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::EQUALITY); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 206 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::INEQUALITY);  }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 207 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::INEQUALITY); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 209 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::LESSER);  }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 210 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::LESSER); }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 212 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::GREATER);  }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 213 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::GREATER); }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 215 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::LESSER_OR_EQUAL);  }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 216 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::LESSER_OR_EQUAL); }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 218 "gen/jc_parser.y"
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].node), ASTBinaryOperator::GREATER_OR_EQUAL);  }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 219 "gen/jc_parser.y"
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[(1) - (3)].node), *(yyvsp[(3) - (3)].statement), ASTBinaryOperator::GREATER_OR_EQUAL); }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 221 "gen/jc_parser.y"
    {  (yyval.function_definition) = new ASTFunctionDefinition(*(yyvsp[(1) - (6)].id), *(yyvsp[(2) - (6)].id), *(yyvsp[(4) - (6)].function_args), *(yyvsp[(6) - (6)].scope_block));  }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 222 "gen/jc_parser.y"
    {  (yyval.function_definition) = new ASTFunctionDefinition(*(yyvsp[(1) - (5)].id), *(yyvsp[(2) - (5)].id), *new ASTFunctionArgs(), *(yyvsp[(5) - (5)].scope_block));  }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 223 "gen/jc_parser.y"
    { (yyval.function_definition) = (yyvsp[(2) - (2)].function_definition); (yyval.function_definition)->SetExporting(true); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 225 "gen/jc_parser.y"
    { (yyval.function_declaration) = new ASTFunctionDeclaration(*(yyvsp[(1) - (5)].id), *(yyvsp[(2) - (5)].id), *new ASTFunctionArgs());  }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 226 "gen/jc_parser.y"
    { (yyval.function_declaration) = new ASTFunctionDeclaration(*(yyvsp[(1) - (6)].id), *(yyvsp[(2) - (6)].id), *(yyvsp[(4) - (6)].function_args));  }
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 228 "gen/jc_parser.y"
    { (yyval.function_declaration) = (yyvsp[(2) - (2)].function_declaration); (yyval.function_declaration)->SetExporting(true); }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 230 "gen/jc_parser.y"
    { (yyval.function_call) = new ASTFunctionCall(*(yyvsp[(1) - (3)].id)); }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 231 "gen/jc_parser.y"
    { (yyval.function_call) = new ASTFunctionCall(*(yyvsp[(1) - (4)].id), *(yyvsp[(3) - (4)].statement_list)); }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 233 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[(1) - (2)].id), *(yyvsp[(2) - (2)].id));  }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 234 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[(1) - (4)].id), *(yyvsp[(2) - (4)].id), *(yyvsp[(4) - (4)].statement));  }
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 237 "gen/jc_parser.y"
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[(1) - (5)].id), *(yyvsp[(2) - (5)].id), *(yyvsp[(4) - (5)].constant_int)); }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 239 "gen/jc_parser.y"
    { (yyval.statement) = new ASTReturnStatement(*(yyvsp[(2) - (2)].statement)); }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 241 "gen/jc_parser.y"
    { (yyval.if_statement) = new ASTIfStatement(*(yyvsp[(1) - (1)].cond_block), NULL); }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 241 "gen/jc_parser.y"
    { (yyval.if_statement) = new ASTIfStatement(*(yyvsp[(1) - (3)].cond_block), (yyvsp[(3) - (3)].scope_block)); }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 244 "gen/jc_parser.y"
    { 
        (yyval.cond_block) = new std::vector<std::unique_ptr<ASTConditionalBlock>>();
        auto cb = std::make_unique<ASTConditionalBlock>(*(yyvsp[(3) - (5)].statement), *(yyvsp[(5) - (5)].scope_block));
        (yyval.cond_block)->push_back(std::move(cb));
    }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 250 "gen/jc_parser.y"
    {
        auto cb = std::make_unique<ASTConditionalBlock>(*(yyvsp[(5) - (7)].statement), *(yyvsp[(7) - (7)].scope_block));
        (yyvsp[(1) - (7)].cond_block)->push_back(std::move(cb));
    }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 255 "gen/jc_parser.y"
    { (yyval.while_loop) = new ASTWhileStatement(*(yyvsp[(3) - (5)].statement), *(yyvsp[(5) - (5)].scope_block)); }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 258 "gen/jc_parser.y"
    {
 (yyval.for_loop) = new ASTForStatement(*(yyvsp[(3) - (9)].statement), *(yyvsp[(5) - (9)].statement), *(yyvsp[(7) - (9)].statement), *(yyvsp[(9) - (9)].scope_block));
}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 262 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(2) - (2)].function_arg)); (yyvsp[(1) - (2)].function_args)->args.push_back(std::move(s)); }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 263 "gen/jc_parser.y"
    { (yyval.function_args) = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(1) - (1)].function_arg)); (yyval.function_args)->args.push_back(std::move(s)); }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 265 "gen/jc_parser.y"
    { (yyval.function_arg) = new ASTFunctionArg(*(yyvsp[(1) - (3)].id), *(yyvsp[(2) - (3)].id)); }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 267 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(3) - (3)].function_arg)); (yyvsp[(1) - (3)].function_args)->args.push_back(std::move(s)); }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 268 "gen/jc_parser.y"
    { (yyval.function_args) = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[(1) - (1)].function_arg)); (yyval.function_args)->args.push_back(std::move(s)); }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 270 "gen/jc_parser.y"
    { auto s = std::unique_ptr<ASTStatement>((yyvsp[(3) - (3)].statement)); (yyvsp[(1) - (3)].statement_list)->push_back(std::move(s)); }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 271 "gen/jc_parser.y"
    { (yyval.statement_list) = new std::vector<std::unique_ptr<ASTStatement>>(); auto s = std::unique_ptr<ASTStatement>((yyvsp[(1) - (1)].statement)); (yyval.statement_list)->push_back(std::move(s)); }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 273 "gen/jc_parser.y"
    { (yyval.function_arg) = new ASTFunctionArg(*(yyvsp[(1) - (2)].id), *(yyvsp[(2) - (2)].id)); }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 273 "gen/jc_parser.y"
    { (yyval.function_arg) = new ASTFunctionArg(); }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 277 "gen/jc_parser.y"
    { (yyval.constant) = new ASTConstantFloat(yylval.fl); }
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 277 "gen/jc_parser.y"
    { (yyval.constant) = new ASTConstantString(yylval.string); }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 279 "gen/jc_parser.y"
    { (yyval.constant_int) = new ASTConstantInt(yylval.integer); }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 281 "gen/jc_parser.y"
    { (yyval.id) = new ASTIdentifier((yyvsp[(1) - (1)].string)); }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 283 "gen/jc_parser.y"
    { (yyval.id) = new ASTIdentifier((yyvsp[(1) - (1)].string)); }
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 283 "gen/jc_parser.y"
    { (yyvsp[(1) - (2)].id)->identifier.append("*");  }
    break;


/* Line 1792 of yacc.c  */
#line 2191 "gen/jc_parser.cpp"
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
#line 285 "gen/jc_parser.y"

