/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  size_t join_length;
  size_t curr_join_length;
  Condition join_conditions[MAX_NUM][MAX_NUM];
  size_t join_conditions_length[MAX_NUM];
  CompOp comp;
  int is_desc;
  AggrType aggr_t;
  char id[MAX_NUM];
  size_t row_num;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->join_length = 0;
  context->row_num = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 137 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_UNIQUE = 8,                     /* UNIQUE  */
  YYSYMBOL_INDEX = 9,                      /* INDEX  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_NE = 45,                        /* NE  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_LK = 47,                        /* LK  */
  YYSYMBOL_MAX_T = 48,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 49,                     /* MIN_T  */
  YYSYMBOL_AVG_T = 50,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 51,                     /* SUM_T  */
  YYSYMBOL_COUNT_T = 52,                   /* COUNT_T  */
  YYSYMBOL_INNER = 53,                     /* INNER  */
  YYSYMBOL_JOIN = 54,                      /* JOIN  */
  YYSYMBOL_TEXT_T = 55,                    /* TEXT_T  */
  YYSYMBOL_NULL_T = 56,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 57,                  /* NULLABLE  */
  YYSYMBOL_IS = 58,                        /* IS  */
  YYSYMBOL_ORDER = 59,                     /* ORDER  */
  YYSYMBOL_BY = 60,                        /* BY  */
  YYSYMBOL_ASC = 61,                       /* ASC  */
  YYSYMBOL_NUMBER = 62,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 63,                     /* FLOAT  */
  YYSYMBOL_ID = 64,                        /* ID  */
  YYSYMBOL_PATH = 65,                      /* PATH  */
  YYSYMBOL_SSS = 66,                       /* SSS  */
  YYSYMBOL_STAR = 67,                      /* STAR  */
  YYSYMBOL_DATE_STR = 68,                  /* DATE_STR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_commands = 71,                  /* commands  */
  YYSYMBOL_command = 72,                   /* command  */
  YYSYMBOL_exit = 73,                      /* exit  */
  YYSYMBOL_help = 74,                      /* help  */
  YYSYMBOL_sync = 75,                      /* sync  */
  YYSYMBOL_begin = 76,                     /* begin  */
  YYSYMBOL_commit = 77,                    /* commit  */
  YYSYMBOL_rollback = 78,                  /* rollback  */
  YYSYMBOL_drop_table = 79,                /* drop_table  */
  YYSYMBOL_show_tables = 80,               /* show_tables  */
  YYSYMBOL_desc_table = 81,                /* desc_table  */
  YYSYMBOL_create_index = 82,              /* create_index  */
  YYSYMBOL_id_list = 83,                   /* id_list  */
  YYSYMBOL_drop_index = 84,                /* drop_index  */
  YYSYMBOL_show_index = 85,                /* show_index  */
  YYSYMBOL_create_table = 86,              /* create_table  */
  YYSYMBOL_attr_def_list = 87,             /* attr_def_list  */
  YYSYMBOL_attr_def = 88,                  /* attr_def  */
  YYSYMBOL_number = 89,                    /* number  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_ID_get = 91,                    /* ID_get  */
  YYSYMBOL_insert = 92,                    /* insert  */
  YYSYMBOL_record_list = 93,               /* record_list  */
  YYSYMBOL_value_list = 94,                /* value_list  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete = 96,                    /* delete  */
  YYSYMBOL_update = 97,                    /* update  */
  YYSYMBOL_update_set = 98,                /* update_set  */
  YYSYMBOL_updates_sets = 99,              /* updates_sets  */
  YYSYMBOL_internal_select = 100,          /* internal_select  */
  YYSYMBOL_select = 101,                   /* select  */
  YYSYMBOL_select_attr = 102,              /* select_attr  */
  YYSYMBOL_attr_list = 103,                /* attr_list  */
  YYSYMBOL_aggr_attr = 104,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 105,                /* aggr_type  */
  YYSYMBOL_extra_attr = 106,               /* extra_attr  */
  YYSYMBOL_rel_name = 107,                 /* rel_name  */
  YYSYMBOL_rel_list = 108,                 /* rel_list  */
  YYSYMBOL_join_list = 109,                /* join_list  */
  YYSYMBOL_inner_join = 110,               /* inner_join  */
  YYSYMBOL_join_condition = 111,           /* join_condition  */
  YYSYMBOL_join_condition_list = 112,      /* join_condition_list  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_condition_list = 114,           /* condition_list  */
  YYSYMBOL_condition = 115,                /* condition  */
  YYSYMBOL_comOp = 116,                    /* comOp  */
  YYSYMBOL_order_by = 117,                 /* order_by  */
  YYSYMBOL_order_attr_list = 118,          /* order_attr_list  */
  YYSYMBOL_order_attr = 119,               /* order_attr  */
  YYSYMBOL_direction = 120,                /* direction  */
  YYSYMBOL_load_data = 121                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   327

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  296

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   160,   160,   162,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   187,   192,   197,   203,   209,   215,   221,   227,
     233,   240,   246,   253,   254,   260,   267,   274,   283,   285,
     289,   299,   309,   319,   329,   341,   344,   345,   346,   347,
     348,   351,   360,   374,   376,   381,   385,   390,   393,   396,
     400,   403,   408,   428,   439,   442,   449,   450,   456,   470,
     492,   497,   502,   507,   511,   513,   520,   527,   532,   537,
     542,   547,   552,   557,   565,   566,   567,   568,   569,   571,
     573,   574,   575,   576,   580,   585,   587,   591,   593,   598,
     605,   615,   623,   633,   642,   651,   661,   672,   674,   678,
     680,   684,   686,   691,   712,   732,   752,   774,   795,   816,
     838,   839,   840,   841,   842,   843,   844,   845,   847,   849,
     853,   855,   860,   866,   874,   877,   880,   885
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "UNIQUE", "INDEX", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "NOT", "LK", "MAX_T", "MIN_T", "AVG_T", "SUM_T",
  "COUNT_T", "INNER", "JOIN", "TEXT_T", "NULL_T", "NULLABLE", "IS",
  "ORDER", "BY", "ASC", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "DATE_STR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "id_list", "drop_index", "show_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "record_list", "value_list", "value", "delete", "update",
  "update_set", "updates_sets", "internal_select", "select", "select_attr",
  "attr_list", "aggr_attr", "aggr_type", "extra_attr", "rel_name",
  "rel_list", "join_list", "inner_join", "join_condition",
  "join_condition_list", "where", "condition_list", "condition", "comOp",
  "order_by", "order_attr_list", "order_attr", "direction", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324
};
#endif

#define YYPACT_NINF (-222)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -222,    99,  -222,    46,    19,   -32,   -51,    93,    11,     0,
       1,     3,    65,    68,    72,    80,    84,    58,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,    37,   107,    59,
      61,    64,  -222,  -222,  -222,  -222,  -222,    15,   103,    97,
     103,   122,   134,   137,   110,  -222,    77,    79,   113,  -222,
    -222,  -222,  -222,  -222,   105,   132,    87,   118,   150,   152,
      83,   102,  -222,  -222,   104,  -222,    18,  -222,  -222,   106,
     136,   141,   114,   121,   126,   133,   135,  -222,  -222,    30,
     103,   103,   103,   143,   179,  -222,  -222,  -222,  -222,    50,
    -222,   188,  -222,   188,   205,   197,   109,   213,   177,   204,
     195,  -222,   207,    -2,   168,   217,   171,  -222,  -222,  -222,
    -222,   187,  -222,   143,   104,   141,   -25,   180,   225,   229,
     230,  -222,   183,    48,   212,   216,  -222,    10,   114,   141,
     254,   126,   243,  -222,  -222,  -222,  -222,  -222,    -6,   245,
     199,   103,   200,  -222,   179,   206,    89,   188,   188,   188,
    -222,  -222,  -222,   247,   203,  -222,  -222,  -222,  -222,  -222,
    -222,   221,  -222,   120,   129,   109,  -222,   259,  -222,  -222,
     204,   267,   208,   207,   268,   211,   218,  -222,   214,   256,
    -222,   240,  -222,   219,   274,   220,  -222,  -222,  -222,   262,
     183,   263,   212,  -222,  -222,  -222,   253,  -222,   216,   -32,
    -222,  -222,   280,  -222,  -222,  -222,   269,  -222,   256,   222,
     270,   138,   226,  -222,   188,  -222,   247,   266,   147,   227,
    -222,   257,  -222,   235,   275,   256,   291,   117,   212,   261,
      -3,   277,  -222,  -222,   281,   294,   271,  -222,  -222,   237,
    -222,   296,  -222,  -222,   238,   156,   165,   138,  -222,  -222,
     239,  -222,  -222,   226,  -222,   183,  -222,   241,   179,  -222,
     212,  -222,  -222,   278,  -222,   261,    -1,   277,   247,  -222,
     141,   174,   242,  -222,  -222,  -222,   286,   290,   282,  -222,
    -222,   266,  -222,   246,  -222,  -222
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,     0,    84,    85,    86,    87,    88,    74,    74,     0,
      74,     0,     0,     0,     0,    24,     0,     0,     0,    25,
      26,    27,    23,    22,     0,     0,     0,     0,     0,     0,
       0,     0,    71,    70,     0,    73,     0,    30,    29,     0,
       0,   109,     0,     0,     0,     0,     0,    28,    35,    74,
      74,    74,    74,    97,    95,    81,    61,    57,    58,    89,
      59,    89,    60,    89,     0,     0,     0,     0,     0,    66,
       0,    51,    38,     0,     0,     0,     0,    75,    77,    78,
      72,     0,    94,    97,     0,   109,     0,     0,     0,     0,
       0,    36,     0,     0,     0,   111,    62,     0,     0,   109,
       0,     0,     0,    46,    47,    48,    50,    49,    42,     0,
       0,    74,     0,    98,    95,   128,    89,    89,    89,    89,
      79,    82,    83,    55,     0,   120,   121,   122,   123,   124,
     125,     0,   126,     0,     0,     0,   110,     0,    64,    65,
      66,     0,     0,    38,     0,     0,     0,    44,     0,    33,
      76,     0,    96,     0,     0,     0,    90,    92,    93,     0,
       0,     0,     0,   127,   115,   113,   116,   114,   111,     0,
      67,    63,     0,    39,    37,    45,     0,    43,    33,     0,
       0,     0,     0,    69,    89,    80,    55,    53,     0,     0,
     112,     0,   137,    40,     0,    33,     0,     0,     0,   107,
     134,   130,    91,    56,     0,     0,     0,   117,   118,     0,
      41,     0,    34,    31,     0,     0,     0,     0,    99,   136,
       0,   135,   132,     0,   129,     0,    52,     0,    95,    32,
       0,   102,   100,   103,   101,   107,   134,   130,    55,   119,
     109,     0,     0,   108,   133,   131,     0,     0,     0,   104,
     105,    53,    68,     0,    54,   106
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -206,  -222,  -222,  -222,   130,   173,  -222,
    -222,  -222,  -222,    21,  -221,   -76,  -222,  -222,   178,   139,
    -222,  -222,   100,   -44,   248,  -222,   -94,   191,  -151,   194,
    -222,    63,    47,  -124,   115,   146,  -132,  -222,    49,    62,
      51,  -222
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   220,    29,    30,    31,   142,   112,   216,
     148,   113,    32,   245,   201,   134,    33,    34,   109,   139,
     179,    35,    49,    72,    50,    51,   128,    94,   125,   122,
     123,   239,   258,   107,   176,   135,   173,   194,   264,   241,
     262,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     103,   155,   174,   192,    73,   243,    75,   129,   259,   130,
     259,   185,   234,    52,    55,   181,    42,    43,    44,    45,
      46,   143,   144,   145,   146,    40,   260,   177,    41,   252,
      56,    96,    47,    57,    70,    48,    95,    97,    98,   156,
     186,   100,   157,   102,    71,   117,   118,   119,   120,    70,
     158,   187,    37,   147,    38,    39,   163,   286,   261,   116,
     261,   178,   196,   197,   198,   199,    96,    58,    59,   126,
     228,    60,    97,    98,    96,    61,   100,   164,   102,   127,
      97,    98,    99,    62,   100,   101,   102,    63,   165,   166,
     167,   168,   169,   170,   171,   172,    64,   205,   207,     2,
      53,    65,    54,     3,     4,   255,   256,   190,   126,     5,
       6,     7,     8,     9,    10,    11,    66,   280,   195,    12,
      13,    14,    70,    67,   226,    68,    15,    16,    69,    74,
     242,    42,    43,    44,    45,    46,    17,    77,   281,    76,
      78,    80,    79,    81,    83,   238,   254,    89,    82,    84,
      90,    85,   247,    87,    86,    88,   287,   165,   166,   167,
     168,   169,   170,   171,   172,    96,    92,   105,    93,   114,
     104,    97,    98,   133,   106,   100,    96,   102,   108,   272,
     274,   238,    97,    98,   204,    96,   100,   110,   102,   278,
     111,    97,    98,   206,    96,   100,   121,   102,   124,   115,
      97,    98,   237,    96,   100,   289,   102,   126,   131,    97,
      98,   246,    96,   100,   132,   102,   136,   137,    97,    98,
     271,    96,   100,   138,   102,   140,   141,    97,    98,   273,
      96,   100,   149,   102,   150,   151,    97,    98,   288,    96,
     100,   152,   102,   160,   159,    97,    98,   161,   162,   100,
     175,   102,   165,   166,   167,   168,   169,   170,   171,   172,
     182,   184,   188,   189,   191,   193,   200,   202,   203,   209,
     211,   214,   212,   215,   217,   219,   221,   223,   218,   222,
     225,   227,   229,   232,   224,   244,   235,   233,   236,   249,
     240,   248,   250,   251,   253,   257,   263,   266,   265,   269,
     267,   268,   270,   276,   291,   279,   290,   282,   292,   231,
     295,   293,   294,   213,   183,   154,   180,   153,    91,   210,
     275,   208,   283,   230,     0,   277,   285,   284
};

static const yytype_int16 yycheck[] =
{
      76,   125,   134,   154,    48,   226,    50,   101,    11,   103,
      11,    17,   218,    64,     3,   139,    48,    49,    50,    51,
      52,    23,    24,    25,    26,     6,    29,    17,     9,   235,
      30,    56,    64,    32,    19,    67,    18,    62,    63,    64,
      46,    66,    67,    68,    29,    89,    90,    91,    92,    19,
     126,    57,     6,    55,     8,     9,   132,   278,    61,    29,
      61,   137,   156,   157,   158,   159,    56,    64,     3,    19,
     202,     3,    62,    63,    56,     3,    66,    29,    68,    29,
      62,    63,    64,     3,    66,    67,    68,     3,    40,    41,
      42,    43,    44,    45,    46,    47,    38,   173,   174,     0,
       7,    64,     9,     4,     5,   237,   238,   151,    19,    10,
      11,    12,    13,    14,    15,    16,     9,   268,    29,    20,
      21,    22,    19,    64,   200,    64,    27,    28,    64,    32,
     224,    48,    49,    50,    51,    52,    37,     3,   270,    17,
       3,    64,    32,    64,    39,   221,    29,    64,    35,    17,
      67,    64,   228,     3,    36,     3,   280,    40,    41,    42,
      43,    44,    45,    46,    47,    56,    64,    31,    64,    36,
      64,    62,    63,    64,    33,    66,    56,    68,    64,   255,
     256,   257,    62,    63,    64,    56,    66,    66,    68,   265,
      64,    62,    63,    64,    56,    66,    53,    68,    19,    64,
      62,    63,    64,    56,    66,   281,    68,    19,     3,    62,
      63,    64,    56,    66,    17,    68,     3,    40,    62,    63,
      64,    56,    66,    19,    68,    30,    19,    62,    63,    64,
      56,    66,    64,    68,    17,    64,    62,    63,    64,    56,
      66,    54,    68,    18,    64,    62,    63,    18,    18,    66,
      34,    68,    40,    41,    42,    43,    44,    45,    46,    47,
       6,    18,    17,    64,    64,    59,    19,    64,    47,    10,
       3,     3,    64,    62,    56,    19,    36,     3,    64,    60,
      18,    18,    29,     3,    64,    19,    64,    18,    18,    32,
      64,    64,    57,    18,     3,    34,    19,     3,    17,     3,
      29,    64,    64,    64,    18,    64,    64,    29,    18,   209,
      64,    29,   291,   183,   141,   124,   138,   123,    70,   180,
     257,   175,   275,   208,    -1,   263,   277,   276
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    86,    92,    96,    97,   101,   121,     6,     8,     9,
       6,     9,    48,    49,    50,    51,    52,    64,    67,   102,
     104,   105,    64,     7,     9,     3,    30,    32,    64,     3,
       3,     3,     3,     3,    38,    64,     9,    64,    64,    64,
      19,    29,   103,   103,    32,   103,    17,     3,     3,    32,
      64,    64,    35,    39,    17,    64,    36,     3,     3,    64,
      67,   104,    64,    64,   107,    18,    56,    62,    63,    64,
      66,    67,    68,    95,    64,    31,    33,   113,    64,    98,
      66,    64,    88,    91,    36,    64,    29,   103,   103,   103,
     103,    53,   109,   110,    19,   108,    19,    29,   106,   106,
     106,     3,    17,    64,    95,   115,     3,    40,    19,    99,
      30,    19,    87,    23,    24,    25,    26,    55,    90,    64,
      17,    64,    54,   109,   107,   113,    64,    67,    95,    64,
      18,    18,    18,    95,    29,    40,    41,    42,    43,    44,
      45,    46,    47,   116,   116,    34,   114,    17,    95,   100,
      98,   113,     6,    88,    18,    17,    46,    57,    17,    64,
     103,    64,   108,    59,   117,    29,   106,   106,   106,   106,
      19,    94,    64,    47,    64,    95,    64,    95,   115,    10,
      99,     3,    64,    87,     3,    62,    89,    56,    64,    19,
      83,    36,    60,     3,    64,    18,    95,    18,   116,    29,
     114,   102,     3,    18,    83,    64,    18,    64,    95,   111,
      64,   119,   106,    94,    19,    93,    64,    95,    64,    32,
      57,    18,    83,     3,    29,   116,   116,    34,   112,    11,
      29,    61,   120,    19,   118,    17,     3,    29,    64,     3,
      64,    64,    95,    64,    95,   111,    64,   119,    95,    64,
     108,   116,    29,   112,   120,   118,    94,   113,    64,    95,
      64,    18,    18,    29,    93,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    82,    83,    83,    84,    85,    86,    87,    87,
      88,    88,    88,    88,    88,    89,    90,    90,    90,    90,
      90,    91,    92,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    96,    97,    98,    98,    99,    99,   100,   101,
     102,   102,   102,   102,   103,   103,   103,   103,   103,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   107,   108,   108,   109,   109,   110,
     111,   111,   111,   111,   111,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,    10,    11,     0,     3,     4,     5,     8,     0,     3,
       5,     6,     2,     4,     3,     1,     1,     1,     1,     1,
       1,     1,    10,     0,     6,     0,     3,     1,     1,     1,
       1,     1,     5,     7,     3,     3,     0,     3,     8,     8,
       2,     2,     4,     2,     0,     3,     5,     3,     3,     5,
       7,     3,     5,     5,     1,     1,     1,     1,     1,     0,
       3,     5,     3,     3,     2,     0,     3,     0,     2,     6,
       3,     3,     3,     3,     5,     5,     7,     0,     3,     0,
       3,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     4,
       0,     3,     2,     4,     0,     1,     1,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 22: /* exit: EXIT SEMICOLON  */
#line 187 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1466 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 192 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1474 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 197 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1482 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 203 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1490 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 209 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1498 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 215 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1506 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 221 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1515 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 227 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1523 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 233 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1532 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 241 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1542 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 247 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1552 "yacc_sql.tab.c"
    break;

  case 34: /* id_list: COMMA ID id_list  */
#line 255 "yacc_sql.y"
                {
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
		}
#line 1560 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1569 "yacc_sql.tab.c"
    break;

  case 36: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;//"show_index";
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1578 "yacc_sql.tab.c"
    break;

  case 37: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 275 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1590 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 285 "yacc_sql.y"
                                   {    }
#line 1596 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 289 "yacc_sql.y"
                                     {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
		CONTEXT->value_length++;
	}
#line 1611 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 299 "yacc_sql.y"
                                                    {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
		CONTEXT->value_length++;
	}
#line 1626 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 309 "yacc_sql.y"
                  {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), (yyvsp[0].number) == TEXTS ? 4096 : 4, 0);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
#line 1641 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NOT NULL_T  */
#line 319 "yacc_sql.y"
                                 {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), (yyvsp[-2].number) == TEXTS ? 4096 : 4, 0);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
#line 1656 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 329 "yacc_sql.y"
                               {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), (yyvsp[-1].number) == TEXTS ? 4096 : 4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
#line 1671 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 341 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1677 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 344 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1683 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 345 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1689 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 346 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1695 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 347 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1701 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 348 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1707 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 352 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1716 "yacc_sql.tab.c"
    break;

  case 52: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE record_list SEMICOLON  */
#line 360 "yacc_sql.y"
                                                                               {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string));
		//临时变量清零
		CONTEXT->row_num=0;
		CONTEXT->value_length=0;
    }
#line 1735 "yacc_sql.tab.c"
    break;

  case 54: /* record_list: COMMA LBRACE value value_list RBRACE record_list  */
#line 376 "yacc_sql.y"
                                                          {

	}
#line 1743 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: %empty  */
#line 381 "yacc_sql.y"
                {
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->row_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1752 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 385 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
#line 1760 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 390 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
	}
#line 1768 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 393 "yacc_sql.y"
            {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
	}
#line 1776 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 396 "yacc_sql.y"
          {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
	}
#line 1785 "yacc_sql.tab.c"
    break;

  case 60: /* value: DATE_STR  */
#line 400 "yacc_sql.y"
                   {
        value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1793 "yacc_sql.tab.c"
    break;

  case 61: /* value: NULL_T  */
#line 403 "yacc_sql.y"
                 {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1801 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 409 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1813 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET update_set updates_sets where SEMICOLON  */
#line 429 "yacc_sql.y"
                {
  			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
  			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), 
						 CONTEXT->conditions, CONTEXT->condition_length);
  			CONTEXT->condition_length = 0;
  			CONTEXT->value_length = 0;
		}
#line 1825 "yacc_sql.tab.c"
    break;

  case 64: /* update_set: ID EQ value  */
#line 439 "yacc_sql.y"
                    {
		updates_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &CONTEXT->values[CONTEXT->value_length - 1]);
	}
#line 1833 "yacc_sql.tab.c"
    break;

  case 65: /* update_set: ID EQ internal_select  */
#line 442 "yacc_sql.y"
                                {
  		value_init_select(&CONTEXT->values[CONTEXT->value_length],
                    &CONTEXT->ssql->selects[CONTEXT->select_length - 1]);
 		updates_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1843 "yacc_sql.tab.c"
    break;

  case 67: /* updates_sets: COMMA update_set updates_sets  */
#line 450 "yacc_sql.y"
                                        {
	
	}
#line 1851 "yacc_sql.tab.c"
    break;

  case 68: /* internal_select: LBRACE SELECT select_attr FROM ID rel_list where RBRACE  */
#line 456 "yacc_sql.y"
                                                                {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
		// selects_reverse_relations(&CONTEXT->ssql->selects[num]);
		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
	}
#line 1867 "yacc_sql.tab.c"
    break;

  case 69: /* select: SELECT select_attr FROM rel_name rel_list where order_by SEMICOLON  */
#line 471 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			// selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);



			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->join_length = 0;
	}
#line 1890 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: STAR attr_list  */
#line 492 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1900 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: ID attr_list  */
#line 497 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1910 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: ID DOT ID attr_list  */
#line 502 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1920 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: aggr_attr attr_list  */
#line 507 "yacc_sql.y"
                              {

	}
#line 1928 "yacc_sql.tab.c"
    break;

  case 75: /* attr_list: COMMA ID attr_list  */
#line 513 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1940 "yacc_sql.tab.c"
    break;

  case 76: /* attr_list: COMMA ID DOT ID attr_list  */
#line 520 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1952 "yacc_sql.tab.c"
    break;

  case 77: /* attr_list: COMMA STAR attr_list  */
#line 527 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1962 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA aggr_attr attr_list  */
#line 532 "yacc_sql.y"
                                   {

	}
#line 1970 "yacc_sql.tab.c"
    break;

  case 79: /* aggr_attr: aggr_type LBRACE ID extra_attr RBRACE  */
#line 537 "yacc_sql.y"
                                               {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, NULL, (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 1980 "yacc_sql.tab.c"
    break;

  case 80: /* aggr_attr: aggr_type LBRACE ID DOT ID extra_attr RBRACE  */
#line 542 "yacc_sql.y"
                                                       {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 1990 "yacc_sql.tab.c"
    break;

  case 81: /* aggr_attr: aggr_type LBRACE RBRACE  */
#line 547 "yacc_sql.y"
                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, INVALID, 0, NULL, NULL, NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 2000 "yacc_sql.tab.c"
    break;

  case 82: /* aggr_attr: aggr_type LBRACE STAR extra_attr RBRACE  */
#line 552 "yacc_sql.y"
                                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t == COUNT ? COUNT : INVALID, 1, NULL, "*", NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 2010 "yacc_sql.tab.c"
    break;

  case 83: /* aggr_attr: aggr_type LBRACE value extra_attr RBRACE  */
#line 557 "yacc_sql.y"
                                                   {
		AggrAttr attr;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggr_init(&attr, CONTEXT->aggr_t, 0, NULL, NULL, value);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2021 "yacc_sql.tab.c"
    break;

  case 84: /* aggr_type: MAX_T  */
#line 565 "yacc_sql.y"
                { CONTEXT->aggr_t = MAX; }
#line 2027 "yacc_sql.tab.c"
    break;

  case 85: /* aggr_type: MIN_T  */
#line 566 "yacc_sql.y"
                { CONTEXT->aggr_t = MIN; }
#line 2033 "yacc_sql.tab.c"
    break;

  case 86: /* aggr_type: AVG_T  */
#line 567 "yacc_sql.y"
                { CONTEXT->aggr_t = AVG; }
#line 2039 "yacc_sql.tab.c"
    break;

  case 87: /* aggr_type: SUM_T  */
#line 568 "yacc_sql.y"
                { CONTEXT->aggr_t = SUM; }
#line 2045 "yacc_sql.tab.c"
    break;

  case 88: /* aggr_type: COUNT_T  */
#line 569 "yacc_sql.y"
                  { CONTEXT->aggr_t = COUNT; }
#line 2051 "yacc_sql.tab.c"
    break;

  case 90: /* extra_attr: COMMA ID extra_attr  */
#line 573 "yacc_sql.y"
                              { CONTEXT->aggr_t = INVALID; }
#line 2057 "yacc_sql.tab.c"
    break;

  case 91: /* extra_attr: COMMA ID DOT ID extra_attr  */
#line 574 "yacc_sql.y"
                                     { CONTEXT->aggr_t = INVALID; }
#line 2063 "yacc_sql.tab.c"
    break;

  case 92: /* extra_attr: COMMA STAR extra_attr  */
#line 575 "yacc_sql.y"
                                { CONTEXT->aggr_t = INVALID; }
#line 2069 "yacc_sql.tab.c"
    break;

  case 93: /* extra_attr: COMMA value extra_attr  */
#line 576 "yacc_sql.y"
                                 { CONTEXT->aggr_t = INVALID; }
#line 2075 "yacc_sql.tab.c"
    break;

  case 94: /* rel_name: ID join_list  */
#line 580 "yacc_sql.y"
                     {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		selects_arrange_relation(&CONTEXT->ssql->sstr.selection, CONTEXT->curr_join_length);
		CONTEXT->curr_join_length=0;
	}
#line 2085 "yacc_sql.tab.c"
    break;

  case 96: /* rel_list: COMMA rel_name rel_list  */
#line 587 "yacc_sql.y"
                              {	
		// selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
	}
#line 2093 "yacc_sql.tab.c"
    break;

  case 98: /* join_list: inner_join join_list  */
#line 593 "yacc_sql.y"
                              {

	}
#line 2101 "yacc_sql.tab.c"
    break;

  case 99: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 598 "yacc_sql.y"
                                                            {
		selects_append_join_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
		CONTEXT->join_length++;
		CONTEXT->curr_join_length++;
		selects_append_join_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->join_conditions[CONTEXT->join_length-1], CONTEXT->join_conditions_length[CONTEXT->join_length-1]);
	}
#line 2112 "yacc_sql.tab.c"
    break;

  case 100: /* join_condition: ID comOp value  */
#line 605 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2127 "yacc_sql.tab.c"
    break;

  case 101: /* join_condition: value comOp value  */
#line 615 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2140 "yacc_sql.tab.c"
    break;

  case 102: /* join_condition: ID comOp ID  */
#line 623 "yacc_sql.y"
                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2155 "yacc_sql.tab.c"
    break;

  case 103: /* join_condition: value comOp ID  */
#line 633 "yacc_sql.y"
                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2169 "yacc_sql.tab.c"
    break;

  case 104: /* join_condition: ID DOT ID comOp value  */
#line 642 "yacc_sql.y"
                            {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2183 "yacc_sql.tab.c"
    break;

  case 105: /* join_condition: value comOp ID DOT ID  */
#line 651 "yacc_sql.y"
                                {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
#line 2198 "yacc_sql.tab.c"
    break;

  case 106: /* join_condition: ID DOT ID comOp ID DOT ID  */
#line 661 "yacc_sql.y"
                                {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
#line 2213 "yacc_sql.tab.c"
    break;

  case 108: /* join_condition_list: AND join_condition join_condition_list  */
#line 674 "yacc_sql.y"
                                                {

	}
#line 2221 "yacc_sql.tab.c"
    break;

  case 110: /* where: WHERE condition condition_list  */
#line 680 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2229 "yacc_sql.tab.c"
    break;

  case 112: /* condition_list: AND condition condition_list  */
#line 686 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2237 "yacc_sql.tab.c"
    break;

  case 113: /* condition: ID comOp value  */
#line 692 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2262 "yacc_sql.tab.c"
    break;

  case 114: /* condition: value comOp value  */
#line 713 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2286 "yacc_sql.tab.c"
    break;

  case 115: /* condition: ID comOp ID  */
#line 733 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2310 "yacc_sql.tab.c"
    break;

  case 116: /* condition: value comOp ID  */
#line 753 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2336 "yacc_sql.tab.c"
    break;

  case 117: /* condition: ID DOT ID comOp value  */
#line 775 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2361 "yacc_sql.tab.c"
    break;

  case 118: /* condition: value comOp ID DOT ID  */
#line 796 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2386 "yacc_sql.tab.c"
    break;

  case 119: /* condition: ID DOT ID comOp ID DOT ID  */
#line 817 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2409 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: EQ  */
#line 838 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2415 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: LT  */
#line 839 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2421 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: GT  */
#line 840 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2427 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: LE  */
#line 841 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2433 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: GE  */
#line 842 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2439 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: NE  */
#line 843 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2445 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: LK  */
#line 844 "yacc_sql.y"
             { CONTEXT->comp = LIKE; }
#line 2451 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: NOT LK  */
#line 845 "yacc_sql.y"
                 { CONTEXT->comp = NOT_LIKE; }
#line 2457 "yacc_sql.tab.c"
    break;

  case 129: /* order_by: ORDER BY order_attr order_attr_list  */
#line 849 "yacc_sql.y"
                                              {

	}
#line 2465 "yacc_sql.tab.c"
    break;

  case 131: /* order_attr_list: COMMA order_attr order_attr_list  */
#line 855 "yacc_sql.y"
                                           {

	}
#line 2473 "yacc_sql.tab.c"
    break;

  case 132: /* order_attr: ID direction  */
#line 860 "yacc_sql.y"
                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
#line 2484 "yacc_sql.tab.c"
    break;

  case 133: /* order_attr: ID DOT ID direction  */
#line 866 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
#line 2495 "yacc_sql.tab.c"
    break;

  case 134: /* direction: %empty  */
#line 874 "yacc_sql.y"
                    {
		CONTEXT->is_desc = 0;
	}
#line 2503 "yacc_sql.tab.c"
    break;

  case 135: /* direction: ASC  */
#line 877 "yacc_sql.y"
              {
		CONTEXT->is_desc = 0;
	}
#line 2511 "yacc_sql.tab.c"
    break;

  case 136: /* direction: DESC  */
#line 880 "yacc_sql.y"
               {
		CONTEXT->is_desc = 1;
	}
#line 2519 "yacc_sql.tab.c"
    break;

  case 137: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 886 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2528 "yacc_sql.tab.c"
    break;


#line 2532 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
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
                      yytoken, &yylval, scanner);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 891 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
