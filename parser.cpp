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
#line 1 "parser.y" /* yacc.c:339  */

#include "yyfunc.h"
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ast * t;


#line 76 "parser.cpp" /* yacc.c:339  */

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
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    t_and = 258,
    t_array = 259,
    t_begin = 260,
    t_boolean = 261,
    t_char = 262,
    t_dispose = 263,
    t_div = 264,
    t_do = 265,
    t_else = 266,
    t_end = 267,
    t_false = 268,
    t_forward = 269,
    t_function = 270,
    t_goto = 271,
    t_if = 272,
    t_integer = 273,
    t_label = 274,
    t_mod = 275,
    t_new = 276,
    t_nil = 277,
    t_not = 278,
    t_of = 279,
    t_or = 280,
    t_procedure = 281,
    t_program = 282,
    t_real = 283,
    t_result = 284,
    t_return = 285,
    t_then = 286,
    t_true = 287,
    t_var = 288,
    t_while = 289,
    t_id = 290,
    t_real_const = 291,
    t_int_const = 292,
    t_char_const = 293,
    t_string_const = 294,
    t_neq = 295,
    t_geq = 296,
    t_leq = 297,
    t_assign = 298,
    unary = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "parser.y" /* yacc.c:355  */

  ast * a;
  char c;
  int n;
  char* s;
  long double r;
  kind k;
  

#line 171 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 188 "parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

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
      58,    59,    49,    47,    56,    48,    55,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    54,
      44,    46,    45,     2,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,    52,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    92,    92,    97,    98,   102,   103,   108,   109,   114,
     115,   116,   117,   122,   123,   124,   125,   130,   131,   136,
     137,   142,   143,   144,   145,   146,   147,   148,   153,   158,
     159,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   182,   183,   188,   189,   194,
     195,   196,   197,   198,   199,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   232,
     233,   238,   239,   240
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"and\"", "\"array\"", "\"begin\"",
  "\"boolean\"", "\"char\"", "\"dispose\"", "\"div\"", "\"do\"",
  "\"else\"", "\"end\"", "\"false\"", "\"forward\"", "\"function\"",
  "\"goto\"", "\"if\"", "\"integer\"", "\"label\"", "\"mod\"", "\"new\"",
  "\"nil\"", "\"not\"", "\"of\"", "\"or\"", "\"procedure\"", "\"program\"",
  "\"real\"", "\"result\"", "\"return\"", "\"then\"", "\"true\"",
  "\"var\"", "\"while\"", "t_id", "t_real_const", "t_int_const",
  "t_char_const", "t_string_const", "\"<>\"", "\">=\"", "\"<=\"", "\":=\"",
  "'<'", "'>'", "'='", "'+'", "'-'", "'*'", "'/'", "'@'", "'^'", "unary",
  "';'", "'.'", "','", "':'", "'('", "')'", "'['", "']'", "$accept",
  "program", "body", "moreid", "localvar", "local", "header", "moreformal",
  "formal", "type", "block", "morestmt", "stmt", "moreexpr", "expr",
  "lvalue", "rvalue", "call", "unop", YY_NULLPTR
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
     295,   296,   297,   298,    60,    62,    61,    43,    45,    42,
      47,    64,    94,   299,    59,    46,    44,    58,    40,    41,
      91,    93
};
# endif

#define YYPACT_NINF -105

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-105)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -16,    -1,    31,   -14,  -105,   352,     9,    40,    18,    22,
      37,    22,    27,   352,    32,  -105,    59,    55,   326,   146,
    -105,  -105,   326,   -30,  -105,   -17,  -105,    79,    39,    13,
    -105,    41,    57,    60,    75,    73,    76,  -105,  -105,  -105,
     352,  -105,    69,   -45,  -105,  -105,  -105,  -105,  -105,    78,
    -105,  -105,  -105,  -105,  -105,   -17,   326,   217,   -45,  -105,
    -105,   326,   326,   -45,   231,     9,   295,    68,  -105,     9,
     326,  -105,   326,  -105,   -27,    22,  -105,    90,    17,    80,
     -17,   -45,   265,    68,    82,   326,   326,   326,   326,     9,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
    -105,   115,     9,  -105,  -105,    83,   183,  -105,  -105,   265,
     149,    22,    87,    88,    91,    85,  -105,  -105,   107,    -8,
    -105,  -105,  -105,  -105,    17,    92,  -105,   -45,  -105,  -105,
    -105,  -105,    72,   126,   123,   123,   123,   123,   123,   123,
      72,    72,  -105,  -105,   -17,  -105,  -105,   326,  -105,   110,
      17,    17,   111,    45,  -105,    17,   140,  -105,    22,     9,
     -45,  -105,    17,  -105,  -105,    17,  -105,  -105,    86,  -105,
    -105,  -105,  -105,   154,    17,  -105
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
      54,    40,     0,    53,    51,     0,    33,     0,    29,     0,
      34,     0,     0,     5,     0,     0,     0,     9,     2,     4,
       0,    53,     0,    43,    39,    57,    61,    81,    56,    53,
      58,    55,    59,    82,    83,     0,     0,     0,    47,    48,
      62,     0,     0,    41,     0,    31,     0,     0,    28,    31,
       0,    50,     0,    12,     0,     0,    10,     0,     0,     0,
       0,    63,     0,    47,    48,     0,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,    31,    38,    79,     0,    45,    52,    30,    32,
       0,     0,     0,     0,     0,    17,     6,    13,     0,     0,
      23,    24,    21,    22,     0,     0,    11,    44,    60,    72,
      69,    70,    71,    35,    74,    78,    76,    75,    77,    73,
      65,    66,    67,    68,     0,    37,    80,     0,    49,     0,
       0,     0,     0,     0,    14,     0,     0,    27,     7,    31,
      42,    46,     0,    15,    20,     0,    18,    25,     0,     8,
      36,    19,    16,     0,     0,    26
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -105,  -105,    -4,    -7,    21,  -105,   173,   -74,  -105,  -104,
      49,   113,   -60,    36,    15,    -6,   128,    -5,  -105
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    12,   113,    37,    13,    14,   114,   115,   125,
      26,    27,    28,   105,   106,    58,    59,    60,    61
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      29,    30,    34,   118,    36,   103,   111,    71,    33,    39,
      43,     1,    20,    63,     6,    72,   155,    16,    41,    67,
     157,   119,    24,   120,   121,    17,    18,    65,    66,   133,
      19,     4,   112,    57,     3,   122,    79,    64,    20,    21,
       5,    25,   145,    22,    23,   123,   163,   164,    24,    81,
      83,   167,   156,    32,    15,     8,    70,    33,   171,    29,
      30,   172,    15,    29,    30,    71,    10,    25,   116,   124,
     175,    82,    35,    72,   127,    85,   100,   101,   111,   166,
      33,    86,    38,    29,    30,   109,    40,   110,    20,    15,
      44,    68,    87,    69,    41,    73,    29,    30,    24,   170,
     129,   130,   131,   132,   149,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,    74,    75,    25,    85,    42,
      71,    98,    99,   111,    86,    33,    85,   107,    72,    76,
      80,    77,    86,    78,   126,    87,    66,   159,   160,   153,
      88,   128,   146,    87,   150,   151,   158,   173,    88,   117,
     152,    36,    85,    29,    30,    90,    91,    92,    86,    93,
      94,    95,    96,    97,    98,    99,   154,   162,   165,    87,
      96,    97,    98,    99,    88,    20,   144,   168,   174,   169,
      31,    41,   108,   161,    84,    24,    85,     0,     0,    90,
      91,    92,    86,    93,    94,    95,    96,    97,    98,    99,
       0,     0,     0,    87,    25,     0,    62,     0,    88,     0,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,     0,     0,    90,    91,    92,    86,    93,    94,    95,
      96,    97,    98,    99,    85,     0,     0,    87,     0,   147,
      86,   102,    88,     0,     0,     0,     0,     0,    89,     0,
       0,    87,     0,     0,     0,     0,    88,    90,    91,    92,
       0,    93,    94,    95,    96,    97,    98,    99,    85,     0,
       0,    90,    91,    92,    86,    93,    94,    95,    96,    97,
      98,    99,     0,     0,     0,    87,     0,     0,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,    92,    45,    93,
      94,    95,    96,    97,    98,    99,     0,    46,    47,     0,
       0,     0,     0,     0,    20,     0,     0,    48,     0,     0,
      49,    50,    51,    52,    24,     0,     0,     0,     0,    45,
       0,     0,    53,    54,     0,     0,    55,     0,    46,    47,
       0,     0,     0,    56,   104,    20,     0,     6,    48,     0,
       0,    49,    50,    51,    52,    24,     7,     8,     0,     0,
       0,     9,     0,    53,    54,     0,     0,    55,    10,     0,
       0,     0,     0,     0,    56,    11
};

static const yytype_int16 yycheck[] =
{
       6,     6,     9,    77,    11,    65,    33,    52,    35,    13,
      16,    27,    29,    19,     5,    60,    24,     8,    35,    25,
     124,     4,    39,     6,     7,    16,    17,    57,    58,    89,
      21,     0,    59,    18,    35,    18,    40,    22,    29,    30,
      54,    58,   102,    34,    35,    28,   150,   151,    39,    55,
      56,   155,    60,    35,     5,    15,    43,    35,   162,    65,
      65,   165,    13,    69,    69,    52,    26,    58,    75,    52,
     174,    56,    35,    60,    80,     3,    61,    62,    33,   153,
      35,     9,    55,    89,    89,    70,    54,    72,    29,    40,
      35,    12,    20,    54,    35,    54,   102,   102,    39,   159,
      85,    86,    87,    88,   111,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,    58,    56,    58,     3,    60,
      52,    49,    50,    33,     9,    35,     3,    59,    60,    54,
      61,    58,     9,    57,    54,    20,    58,    11,   144,    54,
      25,    59,    59,    20,    57,    57,    54,    61,    25,    59,
      59,   158,     3,   159,   159,    40,    41,    42,     9,    44,
      45,    46,    47,    48,    49,    50,    59,    57,    57,    20,
      47,    48,    49,    50,    25,    29,    61,    37,    24,   158,
       7,    35,    69,   147,    56,    39,     3,    -1,    -1,    40,
      41,    42,     9,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    20,    58,    -1,    60,    -1,    25,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    40,    41,    42,     9,    44,    45,    46,
      47,    48,    49,    50,     3,    -1,    -1,    20,    -1,    56,
       9,    10,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    25,    40,    41,    42,
      -1,    44,    45,    46,    47,    48,    49,    50,     3,    -1,
      -1,    40,    41,    42,     9,    44,    45,    46,    47,    48,
      49,    50,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    13,    44,
      45,    46,    47,    48,    49,    50,    -1,    22,    23,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    32,    -1,    -1,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    13,
      -1,    -1,    47,    48,    -1,    -1,    51,    -1,    22,    23,
      -1,    -1,    -1,    58,    59,    29,    -1,     5,    32,    -1,
      -1,    35,    36,    37,    38,    39,    14,    15,    -1,    -1,
      -1,    19,    -1,    47,    48,    -1,    -1,    51,    26,    -1,
      -1,    -1,    -1,    -1,    58,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    63,    35,     0,    54,     5,    14,    15,    19,
      26,    33,    64,    67,    68,    72,     8,    16,    17,    21,
      29,    30,    34,    35,    39,    58,    72,    73,    74,    77,
      79,    68,    35,    35,    65,    35,    65,    66,    55,    64,
      54,    35,    60,    77,    35,    13,    22,    23,    32,    35,
      36,    37,    38,    47,    48,    51,    58,    76,    77,    78,
      79,    80,    60,    77,    76,    57,    58,    77,    12,    54,
      43,    52,    60,    54,    58,    56,    54,    58,    57,    64,
      61,    77,    76,    77,    78,     3,     9,    20,    25,    31,
      40,    41,    42,    44,    45,    46,    47,    48,    49,    50,
      76,    76,    10,    74,    59,    75,    76,    59,    73,    76,
      76,    33,    59,    65,    69,    70,    65,    59,    69,     4,
       6,     7,    18,    28,    52,    71,    54,    77,    59,    76,
      76,    76,    76,    74,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    61,    74,    59,    56,    61,    65,
      57,    57,    59,    54,    59,    24,    60,    71,    54,    11,
      77,    75,    57,    71,    71,    57,    69,    71,    37,    66,
      74,    71,    71,    61,    24,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    67,    67,    68,    68,    68,    68,    69,    69,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     1,     2,     1,     3,     4,     5,     2,
       3,     4,     3,     4,     5,     6,     7,     1,     3,     4,
       3,     1,     1,     1,     1,     3,     6,     2,     3,     1,
       3,     0,     3,     1,     1,     4,     6,     4,     3,     2,
       1,     2,     5,     2,     4,     1,     3,     1,     1,     4,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     1,     1,     1
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
#line 92 "parser.y" /* yacc.c:1646  */
    {t = (yyval.a) = ast_program((yyvsp[-3].s), (yyvsp[-1].a));}
#line 1427 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 97 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_body(NULL, (yyvsp[0].a));}
#line 1433 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 98 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_body((yyvsp[-1].a), (yyvsp[0].a));}
#line 1439 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 102 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_id((yyvsp[0].s), NULL);}
#line 1445 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 103 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_id((yyvsp[-2].s), (yyvsp[0].a));}
#line 1451 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_local_var(ast_local_var_instance((yyvsp[-3].a), (yyvsp[-1].a)), NULL);}
#line 1457 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 109 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_local_var(ast_local_var_instance((yyvsp[-4].a), (yyvsp[-2].a)), (yyvsp[0].a));}
#line 1463 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 114 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_local(LOCAL_VAR, (yyvsp[0].a), NULL);}
#line 1469 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 115 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_local(LABEL, (yyvsp[-1].a), NULL);}
#line 1475 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 116 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_local(DEFINITION, (yyvsp[-3].a), (yyvsp[-1].a));}
#line 1481 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 117 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_local(FORWARD, (yyvsp[-1].a), NULL);}
#line 1487 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 122 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_header(PROCEDURE, (yyvsp[-2].s), NULL, NULL);}
#line 1493 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 123 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_header(PROCEDURE, (yyvsp[-3].s), (yyvsp[-1].a), NULL);}
#line 1499 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 124 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_header(FUNCTION, (yyvsp[-4].s), NULL, (yyvsp[0].a));}
#line 1505 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 125 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_header(FUNCTION, (yyvsp[-5].s), (yyvsp[-3].a), (yyvsp[0].a));}
#line 1511 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 130 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_formal((yyvsp[0].a), NULL);}
#line 1517 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 131 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_formal((yyvsp[-2].a), (yyvsp[0].a));}
#line 1523 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_formal(VARREF, (yyvsp[-2].a), (yyvsp[0].a));}
#line 1529 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 137 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_formal(VAR, (yyvsp[-2].a), (yyvsp[0].a));}
#line 1535 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 142 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(INT, -1, NULL);}
#line 1541 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 143 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(REAL, -1, NULL);}
#line 1547 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 144 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(BOOL, -1, NULL);}
#line 1553 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 145 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(CHAR, -1, NULL);}
#line 1559 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 146 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(ARRAY, -1, (yyvsp[0].a));}
#line 1565 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 147 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(ARRAY, (yyvsp[-3].n), (yyvsp[0].a));}
#line 1571 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 148 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_type(POINTER, -1, (yyvsp[0].a));}
#line 1577 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 153 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_begin((yyvsp[-1].a));}
#line 1583 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 158 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_stmt((yyvsp[0].a), NULL);}
#line 1589 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 159 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_stmt((yyvsp[-2].a), (yyvsp[0].a));}
#line 1595 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 164 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = NULL;}
#line 1601 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 165 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_assign((yyvsp[-2].a), (yyvsp[0].a));}
#line 1607 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 166 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[0].a);}
#line 1613 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[0].a);}
#line 1619 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 168 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_if((yyvsp[-2].a), (yyvsp[0].a), NULL);}
#line 1625 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_if((yyvsp[-4].a), (yyvsp[-2].a), (yyvsp[0].a));}
#line 1631 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 170 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_while((yyvsp[-2].a), (yyvsp[0].a));}
#line 1637 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 171 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_stmt((yyvsp[-2].s), (yyvsp[0].a));}
#line 1643 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 172 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_goto((yyvsp[0].s));}
#line 1649 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 173 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_return();}
#line 1655 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 174 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_new(NULL, (yyvsp[0].a));}
#line 1661 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 175 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_new((yyvsp[-2].a), (yyvsp[0].a));}
#line 1667 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 176 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_dispose((yyvsp[0].a));}
#line 1673 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 177 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_dispose_array((yyvsp[0].a));}
#line 1679 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 182 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_expr((yyvsp[0].a), NULL);}
#line 1685 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 183 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_seq_expr((yyvsp[-2].a), (yyvsp[0].a));}
#line 1691 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 188 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[0].a);}
#line 1697 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 189 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[0].a);}
#line 1703 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 194 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_index((yyvsp[-3].a), (yyvsp[-1].a));}
#line 1709 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 195 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-1].a), REF, NULL);}
#line 1715 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 196 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(STR_CONST, 0, 0, '\0', 0.0, (yyvsp[0].s));}
#line 1721 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 197 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[-1].a);}
#line 1727 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 198 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_id((yyvsp[0].s));}
#line 1733 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 199 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_result();}
#line 1739 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 204 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(INT_CONST, 0, (yyvsp[0].n), '\0', 0.0, NULL);}
#line 1745 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 205 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(BOOL_CONST, 1, 0, '\0', 0.0, NULL);}
#line 1751 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 206 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(BOOL_CONST, 0, 0, '\0', 0.0, NULL);}
#line 1757 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 207 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(REAL_CONST, 0, 0, '\0', (yyvsp[0].r), NULL);}
#line 1763 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(CHAR_CONST, 0, 0, (yyvsp[0].c), 0.0, NULL);}
#line 1769 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 209 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[-1].a);}
#line 1775 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 210 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_const(NIL, 0, 0, '\0', 0.0, NULL);}
#line 1781 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 211 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = (yyvsp[0].a);}
#line 1787 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 212 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[0].a), DEREF, NULL);}
#line 1793 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 213 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[0].a), (yyvsp[-1].k), NULL);}
#line 1799 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), PLUS, (yyvsp[0].a));}
#line 1805 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), MINUS, (yyvsp[0].a));}
#line 1811 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 216 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), TIMES, (yyvsp[0].a));}
#line 1817 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), DIVIDE, (yyvsp[0].a));}
#line 1823 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 218 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), DIV, (yyvsp[0].a));}
#line 1829 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), MOD, (yyvsp[0].a));}
#line 1835 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), OR, (yyvsp[0].a));}
#line 1841 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), AND, (yyvsp[0].a));}
#line 1847 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), EQ, (yyvsp[0].a));}
#line 1853 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 223 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), NEQ, (yyvsp[0].a));}
#line 1859 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 224 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), LESS, (yyvsp[0].a));}
#line 1865 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 225 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), LEQ, (yyvsp[0].a));}
#line 1871 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), GREATER, (yyvsp[0].a));}
#line 1877 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_op((yyvsp[-2].a), GEQ, (yyvsp[0].a));}
#line 1883 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 232 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_call((yyvsp[-2].s), NULL);}
#line 1889 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyval.a) = ast_call((yyvsp[-3].s), (yyvsp[-1].a));}
#line 1895 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 238 "parser.y" /* yacc.c:1646  */
    {(yyval.k) = NOT;}
#line 1901 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 239 "parser.y" /* yacc.c:1646  */
    {(yyval.k) = PLUS;}
#line 1907 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 240 "parser.y" /* yacc.c:1646  */
    {(yyval.k) = MINUS;}
#line 1913 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1917 "parser.cpp" /* yacc.c:1646  */
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
#line 261 "parser.y" /* yacc.c:1906  */


int main() {
  //printf("%lu\n", (long)t);
  int result = yyparse();
  //printf("%s\n", (char*)(t+4));
  //printf("etoimo\n");
  //printf("%lu\n", (long)t);
  if (result == 0) print_ast(t);
  return result;
}