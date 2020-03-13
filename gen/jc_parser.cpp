/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "gen/jc_parser.y" /* yacc.c:339  */

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

#line 106 "gen/jc_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
#line 42 "gen/jc_parser.y" /* yacc.c:355  */

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

#line 222 "gen/jc_parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GEN_JC_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 239 "gen/jc_parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   307

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   131,   131,   133,   134,   136,   136,   138,   139,   141,
     141,   141,   142,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   146,   148,   150,   152,   154,   154,   154,   154,
     154,   156,   156,   158,   158,   160,   160,   162,   162,   162,
     162,   162,   162,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   166,   168,   168,   170,   171,   172,   174,
     176,   178,   180,   182,   184,   185,   187,   188,   190,   191,
     193,   194,   196,   197,   199,   200,   202,   203,   205,   206,
     208,   209,   211,   212,   214,   215,   217,   218,   220,   221,
     222,   224,   225,   227,   228,   229,   231,   233,   235,   235,
     237,   243,   249,   251,   256,   257,   259,   261,   262,   264,
     265,   267,   267,   269,   269,   271,   271,   271,   273,   275,
     277,   277
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
  "assignable_statement", "flow_control", "loop", "scope", "unary_op",
  "binary_op", "assign_op", "member_op", "variable_assign", "cast",
  "increment", "decrement", "address_of", "dereference", "array_index",
  "add", "subtract", "multiply", "divide", "equality", "inequality",
  "lesser", "greater", "lesser_or_equal", "greater_or_equal",
  "function_def", "function_decl", "function_call", "variable_decl",
  "array_decl", "return_statement", "if_statement", "cond_block",
  "while_loop", "for_loop", "struct_list", "struct_pair", "arg_list",
  "statement_list", "arg_pair", "id_or_constant", "constant",
  "constant_int", "id", "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF -143

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-143)))

#define YYTABLE_NINF -19

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      49,  -143,  -143,   268,    56,    72,    77,   104,   105,     2,
     108,   116,    49,  -143,   102,  -143,  -143,  -143,  -143,  -143,
    -143,    98,  -143,    99,  -143,  -143,  -143,  -143,  -143,  -143,
     101,  -143,  -143,    14,     9,  -143,  -143,  -143,   108,   136,
     136,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,   204,  -143,  -143,    24,   268,    49,   268,   134,
     138,   135,     9,    27,  -143,  -143,  -143,   268,   268,     7,
      35,   136,   268,   136,  -143,    12,    25,  -143,  -143,   130,
     250,   268,   268,   268,   268,   268,   268,   268,   268,   256,
     141,   146,   143,  -143,  -143,  -143,   156,   108,  -143,  -143,
     166,   158,  -143,   154,   162,  -143,  -143,  -143,    53,   171,
     268,   152,  -143,  -143,    80,   167,  -143,  -143,    80,  -143,
      80,  -143,    80,  -143,    80,  -143,    80,  -143,    80,  -143,
      80,  -143,    80,  -143,    80,  -143,  -143,     5,   170,   268,
     170,   133,    46,  -143,     9,  -143,   268,   208,  -143,   165,
     172,   173,   174,    98,    99,    10,   268,  -143,  -143,    31,
     168,    63,  -143,     9,   169,  -143,  -143,  -143,   175,   176,
    -143,   268,  -143,   180,  -143,   181,    67,  -143,  -143,   182,
    -143,  -143,  -143,  -143,  -143,  -143,   177,  -143,  -143,   193,
      51,     6,  -143,  -143,  -143,   268,   201,  -143,   170,  -143,
    -143,  -143,  -143,   178,  -143,   170,  -143
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   119,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     3,     5,    19,    20,    21,    18,    32,
      17,     0,    53,     0,    14,    15,    16,    95,    13,    31,
      98,    33,    34,     0,     0,   117,   118,   116,     0,     0,
       0,    97,    27,    28,    29,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    26,    30,   114,   115,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     4,     6,     0,     0,     0,
       0,     0,     0,     0,   121,    93,     0,    63,    62,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    22,    90,     0,     0,    58,    57,
       0,     0,    99,     0,     0,    54,    56,    55,     0,     0,
       0,     0,    60,    67,    66,   113,    61,    69,    68,    71,
      70,    73,    72,    75,    74,    77,    76,    81,    80,    85,
      84,    79,    78,    83,    82,    91,   110,     0,     0,     0,
       0,     0,     0,   105,     0,    36,     0,     0,     7,     0,
       0,     0,    11,    29,    42,   113,     0,    64,    65,     0,
       0,     0,   108,     0,     0,    94,    59,   113,     0,     0,
      92,     0,   100,     0,   102,     0,     0,    24,   104,     0,
      25,    35,     8,     9,    12,    10,     0,    88,    87,     0,
       0,     0,   111,    96,   109,     0,     0,   106,     0,   112,
      89,    86,   107,     0,   101,     0,   103
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,  -143,   179,  -143,    52,   -62,  -143,  -143,  -143,
    -143,    -3,  -103,  -143,  -142,   209,  -143,  -143,     3,  -143,
    -143,  -143,  -143,  -143,  -143,     4,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,   211,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,    66,    74,  -143,
      32,    33,  -143,   -70,    11,    -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,   157,   158,    14,    15,    16,    17,
     160,   161,    18,    19,   112,    42,    43,    20,    44,    22,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    24,    25,    61,    26,
      27,    28,    29,    30,    31,    32,   152,   153,   171,   147,
     172,    62,    63,    64,    65,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    72,    73,    21,    23,   101,   182,   162,   184,     2,
     113,    33,     1,     2,   180,    21,    23,   110,    99,   181,
     118,   170,    80,    33,   119,    81,    80,   198,    84,    81,
      86,    82,    99,   120,   121,    82,    80,   107,     1,    81,
      36,   110,   111,     9,    84,    85,    84,   197,   159,   174,
      87,    88,     1,     2,   162,    83,     2,   187,   211,    83,
       2,   110,   169,   100,    66,   102,   214,   210,   170,    83,
      21,    23,   200,   216,   108,   109,   206,   201,    33,   116,
      67,   201,     3,   106,     4,    68,     5,     6,     7,     8,
       9,   114,   115,    10,   117,   159,   146,   178,   179,   154,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     173,    69,    70,   163,   164,     2,    74,   175,    76,    77,
      78,   165,   124,   128,   130,   132,   134,   136,   138,   140,
     142,   144,   177,     1,    35,    36,    37,    79,    38,     1,
       2,   103,   185,   173,   154,   104,   183,   122,   170,    39,
     148,   105,   150,   190,   176,     1,    35,    36,    37,    40,
     163,   164,   149,   196,   151,   189,   166,   167,   165,     1,
      35,    36,    37,     2,    38,   168,    36,   155,   204,    80,
     110,   193,   203,   199,   202,    39,   208,   215,   194,   195,
     -18,    75,   122,   173,   126,    40,   205,   197,   207,     3,
     156,     4,   213,     5,     6,     7,     8,     9,   209,   192,
      10,     1,    35,    36,    37,     2,    38,   210,   188,   191,
      71,    89,    90,    91,    92,   186,    93,    39,    94,    95,
      96,    97,    98,   212,     0,     0,     0,    40,     0,     0,
       0,     3,   156,     4,     0,     5,     6,     7,     8,     9,
       0,     0,    10,     1,    35,    36,    37,     0,    38,     1,
      35,    36,    37,     0,    38,   145,     0,     0,   126,    39,
       0,     1,    35,    36,    37,    39,    38,     0,     0,    40,
       0,     0,     0,     0,     0,    40,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    40,   123,   127,
     129,   131,   133,   135,   137,   139,   141,   143
};

static const yytype_int16 yycheck[] =
{
       3,     9,    10,     0,     0,    67,   148,   110,   150,     7,
      80,     0,     3,     7,     9,    12,    12,    10,     8,    14,
       8,    15,    12,    12,    12,    15,    12,   169,    19,    15,
      38,    21,     8,    21,     9,    21,    12,    10,     3,    15,
       5,    10,    35,    41,    19,    34,    19,    16,   110,   119,
      39,    40,     3,     7,   157,    45,     7,    11,   200,    45,
       7,    10,     9,    66,     8,    68,   208,    16,    15,    45,
      67,    67,     9,   215,    77,    78,     9,    14,    67,    82,
       8,    14,    33,    72,    35,     8,    37,    38,    39,    40,
      41,    80,    81,    44,    83,   157,    99,    17,    18,   107,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     118,     7,     7,   110,   110,     7,     0,   120,    16,    21,
      21,   110,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,   121,     3,     4,     5,     6,    36,     8,     3,
       7,     7,     9,   151,   152,     7,   149,    17,    15,    19,
       9,    16,     9,   156,   121,     3,     4,     5,     6,    29,
     157,   157,    16,   166,     8,   154,     8,    13,   157,     3,
       4,     5,     6,     7,     8,    13,     5,    11,   181,    12,
      10,    16,    13,    15,   173,    19,     9,     9,    16,    16,
      16,    12,    17,   201,    18,    29,    16,    16,    16,    33,
      34,    35,   205,    37,    38,    39,    40,    41,    15,   157,
      44,     3,     4,     5,     6,     7,     8,    16,   152,    11,
       9,    17,    18,    19,    20,   151,    22,    19,    24,    25,
      26,    27,    28,   201,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    33,    34,    35,    -1,    37,    38,    39,    40,    41,
      -1,    -1,    44,     3,     4,     5,     6,    -1,     8,     3,
       4,     5,     6,    -1,     8,     9,    -1,    -1,    18,    19,
      -1,     3,     4,     5,     6,    19,     8,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,    33,    35,    37,    38,    39,    40,    41,
      44,    48,    49,    50,    53,    54,    55,    56,    59,    60,
      64,    65,    66,    72,    83,    84,    86,    87,    88,    89,
      90,    91,    92,   101,   102,     4,     5,     6,     8,    19,
      29,    58,    62,    63,    65,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    85,    98,    99,   100,   101,     8,     8,     8,     7,
       7,    84,   102,   102,     0,    50,    16,    21,    21,    36,
      12,    15,    21,    45,    19,   101,   102,   101,   101,    17,
      18,    19,    20,    22,    24,    25,    26,    27,    28,     8,
      58,    53,    58,     7,     7,    16,   101,    10,    58,    58,
      10,    35,    61,   100,   101,   101,    58,   101,     8,    12,
      21,     9,    17,    62,    98,   101,    18,    62,    98,    62,
      98,    62,    98,    62,    98,    62,    98,    62,    98,    62,
      98,    62,    98,    62,    98,     9,    58,    96,     9,    16,
       9,     8,    93,    94,   102,    11,    34,    51,    52,    53,
      57,    58,    59,    65,    72,   101,     8,    13,    13,     9,
      15,    95,    97,   102,   100,    58,    98,   101,    17,    18,
       9,    14,    61,    58,    61,     9,    95,    11,    94,   101,
      58,    11,    52,    16,    16,    16,    58,    16,    61,    15,
       9,    14,   101,    13,    58,    16,     9,    16,     9,    15,
      16,    61,    97,    58,    61,     9,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    55,    56,    57,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      62,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    64,    65,    65,    66,    66,    66,    67,
      68,    69,    70,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    78,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    85,    85,    86,    86,    86,    87,    88,    89,    89,
      90,    90,    91,    92,    93,    93,    94,    95,    95,    96,
      96,    97,    97,    98,    98,    99,    99,    99,   100,   101,
     102,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     1,     2,     2,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     5,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     4,
       3,     3,     2,     2,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     6,     5,     5,     6,
       3,     3,     4,     2,     4,     1,     5,     2,     1,     3,
       5,     7,     5,     9,     2,     1,     3,     3,     1,     3,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 131 "gen/jc_parser.y" /* yacc.c:1646  */
    { base = std::make_unique<ASTBlock>(); std::unique_ptr<ASTBlock> b = std::unique_ptr<ASTBlock>((yyvsp[0].scope_block)); base->block->push_back(std::move(b)); }
#line 1501 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 133 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.scope_block) = new ASTBlock(); auto s = std::unique_ptr<ASTStatement>((yyvsp[0].statement)); (yyval.scope_block)->block->push_back(std::move(s)); }
#line 1507 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 134 "gen/jc_parser.y" /* yacc.c:1646  */
    { auto s = std::unique_ptr<ASTStatement>((yyvsp[0].statement)); (yyvsp[-1].scope_block)->block->push_back(std::move(s)); }
#line 1513 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 136 "gen/jc_parser.y" /* yacc.c:1646  */
    { SetNodeInfo(*(yyval.statement)); }
#line 1519 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 136 "gen/jc_parser.y" /* yacc.c:1646  */
    { SetNodeInfo(*(yyval.statement)); }
#line 1525 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 138 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.scope_block) = new ASTBlock(); auto statement = std::unique_ptr<ASTStatement>((yyvsp[0].statement)); (yyval.scope_block)->block->push_back(std::move(statement)); SetNodeInfo(*(yyval.scope_block)); }
#line 1531 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 139 "gen/jc_parser.y" /* yacc.c:1646  */
    { auto statement = std::unique_ptr<ASTStatement>((yyvsp[0].statement)); (yyvsp[-1].scope_block)->block->push_back(std::move(statement)); }
#line 1537 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 141 "gen/jc_parser.y" /* yacc.c:1646  */
    { SetNodeInfo(*(yyvsp[-1].statement)); }
#line 1543 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 141 "gen/jc_parser.y" /* yacc.c:1646  */
    { SetNodeInfo(*(yyvsp[-1].statement)); }
#line 1549 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 141 "gen/jc_parser.y" /* yacc.c:1646  */
    { SetNodeInfo(*(yyvsp[0].statement)); }
#line 1555 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 142 "gen/jc_parser.y" /* yacc.c:1646  */
    { SetNodeInfo(*(yyvsp[-1].defer_statement)); }
#line 1561 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 146 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.type_mod) = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::ALIAS); }
#line 1567 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 148 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.type_mod) = new ASTTypeSystemModStatement(ASTTypeSystemModStatement::TYPE_MOD_OP::TYPEDEF); }
#line 1573 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 150 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTStructDefinition(*(yyvsp[-3].id), *(yyvsp[-1].function_args)); }
#line 1579 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 152 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.defer_statement) = new ASTDeferredStatement(*(yyvsp[0].statement)); }
#line 1585 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 160 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.scope_block) = (yyvsp[-1].scope_block); }
#line 1591 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 160 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.scope_block) = new ASTBlock(); }
#line 1597 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 168 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTMemberOperator(*(yyvsp[-2].id), *(yyvsp[0].id), ASTMemberOperator::OP::DOT); }
#line 1603 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 168 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTMemberOperator(*(yyvsp[-2].id), *(yyvsp[0].id), ASTMemberOperator::OP::ARROW); }
#line 1609 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 170 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[-2].id), *(yyvsp[0].statement));  }
#line 1615 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 171 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[-2].unary_operator), *(yyvsp[0].statement)); }
#line 1621 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 172 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTVariableAssignment(*(yyvsp[-2].statement), *(yyvsp[0].statement)); }
#line 1627 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 174 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[0].node), (yyvsp[-2].id), ASTUnaryOperator::CAST); }
#line 1633 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 176 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[-2].node), ASTUnaryOperator::INCREMENT);  }
#line 1639 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 178 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[-2].node), ASTUnaryOperator::DECREMENT);  }
#line 1645 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 180 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[0].id), ASTUnaryOperator::ADDRESS_OF); }
#line 1651 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 182 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[0].id), ASTUnaryOperator::DEREFERENCE); }
#line 1657 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 184 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[-3].id), *(yyvsp[-1].constant_int), ASTUnaryOperator::ARRAY_INDEX); }
#line 1663 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 185 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.unary_operator) = new ASTUnaryOperator(*(yyvsp[-3].id), (yyvsp[-1].id), ASTUnaryOperator::ARRAY_INDEX);}
#line 1669 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 187 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::ADD);  }
#line 1675 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 188 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::ADD); }
#line 1681 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 190 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::SUBTRACT);  }
#line 1687 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 191 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::SUBTRACT); }
#line 1693 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 193 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::MULTIPLY);  }
#line 1699 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 194 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::MULTIPLY); }
#line 1705 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 196 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::DIVIDE);  }
#line 1711 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 197 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::DIVIDE); }
#line 1717 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 199 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::EQUALITY);  }
#line 1723 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 200 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::EQUALITY); }
#line 1729 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 202 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::INEQUALITY);  }
#line 1735 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 203 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::INEQUALITY); }
#line 1741 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 205 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::LESSER);  }
#line 1747 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 206 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::LESSER); }
#line 1753 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 208 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::GREATER);  }
#line 1759 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 209 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::GREATER); }
#line 1765 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 211 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::LESSER_OR_EQUAL);  }
#line 1771 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 212 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::LESSER_OR_EQUAL); }
#line 1777 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 214 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].node), ASTBinaryOperator::GREATER_OR_EQUAL);  }
#line 1783 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 215 "gen/jc_parser.y" /* yacc.c:1646  */
    {(yyval.statement) = new ASTBinaryOperator(*(yyvsp[-2].node), *(yyvsp[0].statement), ASTBinaryOperator::GREATER_OR_EQUAL); }
#line 1789 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 217 "gen/jc_parser.y" /* yacc.c:1646  */
    {  (yyval.statement) = new ASTFunctionDefinition(*(yyvsp[-5].id), *(yyvsp[-4].id), *(yyvsp[-2].function_args), *(yyvsp[0].scope_block));  }
#line 1795 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 218 "gen/jc_parser.y" /* yacc.c:1646  */
    {  (yyval.statement) = new ASTFunctionDefinition(*(yyvsp[-4].id), *(yyvsp[-3].id), *new ASTFunctionArgs(), *(yyvsp[0].scope_block));  }
#line 1801 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 220 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTFunctionDeclaration(*(yyvsp[-4].id), *(yyvsp[-3].id), *new ASTFunctionArgs());  }
#line 1807 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 221 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTFunctionDeclaration(*(yyvsp[-5].id), *(yyvsp[-4].id), *(yyvsp[-2].function_args));  }
#line 1813 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 224 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_call) = new ASTFunctionCall(*(yyvsp[-2].id)); }
#line 1819 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 225 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_call) = new ASTFunctionCall(*(yyvsp[-3].id), *(yyvsp[-1].statement_list)); }
#line 1825 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 227 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[-1].id), *(yyvsp[0].id));  }
#line 1831 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 228 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[-3].id), *(yyvsp[-2].id), *(yyvsp[0].statement));  }
#line 1837 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 231 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTVariableDeclaration(*(yyvsp[-4].id), *(yyvsp[-3].id), *(yyvsp[-1].constant_int)); }
#line 1843 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 233 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ASTReturnStatement(*(yyvsp[0].statement)); }
#line 1849 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 235 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.if_statement) = new ASTIfStatement(*(yyvsp[0].cond_block), NULL); }
#line 1855 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 235 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.if_statement) = new ASTIfStatement(*(yyvsp[-2].cond_block), (yyvsp[0].scope_block)); }
#line 1861 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 238 "gen/jc_parser.y" /* yacc.c:1646  */
    { 
        (yyval.cond_block) = new std::vector<std::unique_ptr<ASTConditionalBlock>>();
        auto cb = std::make_unique<ASTConditionalBlock>(*(yyvsp[-2].statement), *(yyvsp[0].scope_block));
        (yyval.cond_block)->push_back(std::move(cb));
    }
#line 1871 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 244 "gen/jc_parser.y" /* yacc.c:1646  */
    {
        auto cb = std::make_unique<ASTConditionalBlock>(*(yyvsp[-2].statement), *(yyvsp[0].scope_block));
        (yyvsp[-6].cond_block)->push_back(std::move(cb));
    }
#line 1880 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 249 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.while_loop) = new ASTWhileStatement(*(yyvsp[-2].statement), *(yyvsp[0].scope_block)); }
#line 1886 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 252 "gen/jc_parser.y" /* yacc.c:1646  */
    {
 (yyval.for_loop) = new ASTForStatement(*(yyvsp[-6].statement), *(yyvsp[-4].statement), *(yyvsp[-2].statement), *(yyvsp[0].scope_block));
}
#line 1894 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 256 "gen/jc_parser.y" /* yacc.c:1646  */
    { auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[0].function_arg)); (yyvsp[-1].function_args)->args.push_back(std::move(s)); }
#line 1900 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 257 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_args) = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[0].function_arg)); (yyval.function_args)->args.push_back(std::move(s)); }
#line 1906 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 259 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_arg) = new ASTFunctionArg(*(yyvsp[-2].id), *(yyvsp[-1].id)); }
#line 1912 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 261 "gen/jc_parser.y" /* yacc.c:1646  */
    { auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[0].function_arg)); (yyvsp[-2].function_args)->args.push_back(std::move(s)); }
#line 1918 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 262 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_args) = new ASTFunctionArgs(); auto s = std::unique_ptr<ASTFunctionArg>((yyvsp[0].function_arg)); (yyval.function_args)->args.push_back(std::move(s)); }
#line 1924 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 264 "gen/jc_parser.y" /* yacc.c:1646  */
    { auto s = std::unique_ptr<ASTStatement>((yyvsp[0].statement)); (yyvsp[-2].statement_list)->push_back(std::move(s)); }
#line 1930 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 265 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.statement_list) = new std::vector<std::unique_ptr<ASTStatement>>(); auto s = std::unique_ptr<ASTStatement>((yyvsp[0].statement)); (yyval.statement_list)->push_back(std::move(s)); }
#line 1936 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 267 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_arg) = new ASTFunctionArg(*(yyvsp[-1].id), *(yyvsp[0].id)); }
#line 1942 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 267 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.function_arg) = new ASTFunctionArg(); }
#line 1948 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 271 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.constant) = new ASTConstantFloat(yylval.fl); }
#line 1954 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 271 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.constant) = new ASTConstantString(yylval.string); }
#line 1960 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 273 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.constant_int) = new ASTConstantInt(yylval.integer); }
#line 1966 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 275 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.id) = new ASTIdentifier((yyvsp[0].string)); }
#line 1972 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 277 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyval.id) = new ASTIdentifier((yyvsp[0].string)); }
#line 1978 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 277 "gen/jc_parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].id)->identifier.append("*");  }
#line 1984 "gen/jc_parser.cpp" /* yacc.c:1646  */
    break;


#line 1988 "gen/jc_parser.cpp" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 279 "gen/jc_parser.y" /* yacc.c:1906  */

