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
  Selects selects[MAX_NUM];
  size_t condition_length[MAX_NUM];
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM][MAX_NUM];
  size_t join_length;
  size_t curr_join_length;
  Condition join_conditions[MAX_NUM][MAX_NUM];
  size_t join_conditions_length[MAX_NUM];
  CompOp comp[MAX_NUM];
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
  context->condition_length[0] = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->join_length = 0;
  context->row_num = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 138 "yacc_sql.tab.c"

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
  YYSYMBOL_IN = 62,                        /* IN  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_DATE_STR = 69,                  /* DATE_STR  */
  YYSYMBOL_STRING_V = 70,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_commands = 72,                  /* commands  */
  YYSYMBOL_command = 73,                   /* command  */
  YYSYMBOL_exit = 74,                      /* exit  */
  YYSYMBOL_help = 75,                      /* help  */
  YYSYMBOL_sync = 76,                      /* sync  */
  YYSYMBOL_begin = 77,                     /* begin  */
  YYSYMBOL_commit = 78,                    /* commit  */
  YYSYMBOL_rollback = 79,                  /* rollback  */
  YYSYMBOL_drop_table = 80,                /* drop_table  */
  YYSYMBOL_show_tables = 81,               /* show_tables  */
  YYSYMBOL_desc_table = 82,                /* desc_table  */
  YYSYMBOL_create_index = 83,              /* create_index  */
  YYSYMBOL_id_list = 84,                   /* id_list  */
  YYSYMBOL_drop_index = 85,                /* drop_index  */
  YYSYMBOL_show_index = 86,                /* show_index  */
  YYSYMBOL_create_table = 87,              /* create_table  */
  YYSYMBOL_attr_def_list = 88,             /* attr_def_list  */
  YYSYMBOL_attr_def = 89,                  /* attr_def  */
  YYSYMBOL_number = 90,                    /* number  */
  YYSYMBOL_type = 91,                      /* type  */
  YYSYMBOL_ID_get = 92,                    /* ID_get  */
  YYSYMBOL_insert = 93,                    /* insert  */
  YYSYMBOL_record_list = 94,               /* record_list  */
  YYSYMBOL_value_list = 95,                /* value_list  */
  YYSYMBOL_value = 96,                     /* value  */
  YYSYMBOL_delete_begin = 97,              /* delete_begin  */
  YYSYMBOL_delete = 98,                    /* delete  */
  YYSYMBOL_update_begin = 99,              /* update_begin  */
  YYSYMBOL_update = 100,                   /* update  */
  YYSYMBOL_update_set = 101,               /* update_set  */
  YYSYMBOL_updates_sets = 102,             /* updates_sets  */
  YYSYMBOL_select_begin = 103,             /* select_begin  */
  YYSYMBOL_sub_select = 104,               /* sub_select  */
  YYSYMBOL_select = 105,                   /* select  */
  YYSYMBOL_select_attr = 106,              /* select_attr  */
  YYSYMBOL_attr_list = 107,                /* attr_list  */
  YYSYMBOL_aggr_attr = 108,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 109,                /* aggr_type  */
  YYSYMBOL_extra_attr = 110,               /* extra_attr  */
  YYSYMBOL_rel_name = 111,                 /* rel_name  */
  YYSYMBOL_rel_list = 112,                 /* rel_list  */
  YYSYMBOL_join_list = 113,                /* join_list  */
  YYSYMBOL_inner_join = 114,               /* inner_join  */
  YYSYMBOL_join_condition = 115,           /* join_condition  */
  YYSYMBOL_join_condition_list = 116,      /* join_condition_list  */
  YYSYMBOL_where = 117,                    /* where  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_comOp = 120,                    /* comOp  */
  YYSYMBOL_order_by = 121,                 /* order_by  */
  YYSYMBOL_order_attr_list = 122,          /* order_attr_list  */
  YYSYMBOL_order_attr = 123,               /* order_attr  */
  YYSYMBOL_direction = 124,                /* direction  */
  YYSYMBOL_load_data = 125                 /* load_data  */
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
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  298

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   162,   162,   164,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   189,   194,   199,   205,   211,   217,   223,   229,
     235,   242,   248,   255,   256,   262,   269,   276,   285,   287,
     291,   301,   311,   321,   331,   343,   346,   347,   348,   349,
     350,   353,   362,   376,   378,   383,   387,   392,   395,   398,
     402,   405,   408,   414,   419,   431,   436,   449,   454,   455,
     460,   465,   470,   483,   488,   493,   498,   502,   504,   509,
     514,   519,   523,   528,   533,   538,   543,   551,   552,   553,
     554,   555,   557,   559,   560,   561,   562,   565,   570,   572,
     575,   577,   583,   590,   600,   608,   618,   627,   636,   646,
     657,   659,   662,   664,   667,   669,   673,   683,   691,   702,
     711,   720,   730,   742,   743,   744,   745,   746,   747,   748,
     749,   750,   751,   752,   753,   755,   757,   760,   762,   767,
     773,   781,   784,   787,   792
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
  "ORDER", "BY", "ASC", "IN", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "DATE_STR", "STRING_V", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "id_list", "drop_index",
  "show_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "record_list", "value_list", "value",
  "delete_begin", "delete", "update_begin", "update", "update_set",
  "updates_sets", "select_begin", "sub_select", "select", "select_attr",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325
};
#endif

#define YYPACT_NINF (-226)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -226,   215,  -226,    80,    42,  -226,   -34,    66,    36,    34,
    -226,  -226,    78,    84,    87,    88,    92,    31,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,    67,  -226,    32,  -226,   -36,    97,  -226,
    -226,    37,    96,    41,    43,    44,    98,   104,    82,  -226,
      51,  -226,  -226,  -226,  -226,  -226,    81,    57,    89,  -226,
    -226,  -226,  -226,  -226,    -2,   108,    91,   108,   116,  -226,
     119,    72,   102,   136,   137,  -226,  -226,    76,   112,    77,
     113,    93,   250,    94,  -226,  -226,    95,  -226,    -7,   110,
     120,   114,  -226,  -226,   151,   145,   133,    29,   164,   129,
     161,     7,   108,   108,   108,   131,   169,   163,  -226,  -226,
    -226,  -226,     9,  -226,   170,  -226,   170,  -226,   171,    -1,
     126,   175,  -226,   154,   190,   204,   235,   167,  -226,   154,
      93,   113,   138,  -226,  -226,  -226,  -226,   148,  -226,   131,
      95,   113,   186,     3,   140,   188,   194,   196,   110,   198,
    -226,  -226,  -226,  -226,  -226,    17,   205,   159,   213,   173,
     174,  -226,  -226,  -226,  -226,  -226,  -226,   -43,  -226,   195,
    -226,    48,    65,    29,  -226,  -226,   161,   231,   108,   189,
    -226,   169,   181,  -226,    11,   170,   170,   170,  -226,  -226,
    -226,   171,   252,   197,   201,  -226,   193,   234,   154,   241,
     258,   235,  -226,  -226,  -226,  -226,  -226,   236,  -226,   167,
    -226,  -226,  -226,   228,  -226,   203,  -226,   218,  -226,  -226,
    -226,   266,  -226,  -226,  -226,   268,  -226,   234,   222,   270,
     213,   271,  -226,    86,   226,  -226,   101,   229,   170,  -226,
     238,   274,   234,   293,  -226,   286,   301,   276,  -226,  -226,
     227,   235,   272,    -8,   288,  -226,  -226,   305,  -226,  -226,
     154,  -226,   244,   245,   118,   130,   101,  -226,  -226,   246,
    -226,  -226,   229,  -226,  -226,   213,  -226,   235,  -226,  -226,
     283,  -226,   272,    -9,   288,   295,   144,   249,  -226,  -226,
    -226,   271,   287,  -226,  -226,  -226,   254,  -226
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    70,     0,     0,     0,     0,
      63,    65,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     0,     7,     0,     6,     0,     0,     4,
      19,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,    25,    26,    27,    23,    22,     0,     0,     0,    87,
      88,    89,    90,    91,    77,    77,     0,    77,     0,    72,
       0,     0,     0,     0,     0,    30,    29,     0,     0,     0,
     112,     0,     0,     0,    74,    73,     0,    76,     0,     0,
       0,     0,    28,    35,     0,     0,     0,     0,     0,     0,
      68,    77,    77,    77,    77,   100,    98,     0,    84,    61,
      57,    58,    92,    59,    92,    60,    92,    51,    38,     0,
       0,     0,    36,     0,     0,     0,     0,   114,    64,     0,
       0,   112,     0,    78,    80,    81,    75,     0,    97,   100,
       0,   112,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    47,    48,    50,    49,    42,     0,     0,    55,     0,
       0,   123,   124,   125,   126,   127,   128,     0,   129,   131,
     133,     0,     0,     0,   113,    67,    68,     0,    77,     0,
     101,    98,   135,    62,    92,    92,    92,    92,    82,    85,
      86,    38,     0,     0,     0,    44,     0,    33,     0,     0,
       0,     0,   130,   134,   132,   118,   116,   119,   117,   114,
      69,    66,    79,     0,    99,     0,    71,     0,    93,    95,
      96,     0,    39,    37,    45,     0,    43,    33,     0,     0,
      55,    53,   144,     0,     0,   115,     0,     0,    92,    83,
      40,     0,    33,     0,    56,     0,     0,     0,   120,   121,
       0,     0,   110,   141,   137,    94,    41,     0,    34,    31,
       0,    52,     0,     0,     0,     0,     0,   102,   143,     0,
     142,   139,     0,   136,    32,    55,   122,     0,   105,   103,
     106,   104,   110,   141,   137,     0,     0,     0,   111,   140,
     138,    53,     0,   107,   108,    54,     0,   109
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -209,  -226,  -226,  -226,   132,   172,  -226,
    -226,  -226,  -226,    26,  -225,   -88,  -226,  -226,  -226,  -226,
     191,   146,  -226,   217,  -226,  -226,   -59,   243,  -226,  -107,
     187,   147,   192,  -226,    60,    47,   -94,   121,   160,  -125,
    -226,    50,    63,    49,  -226
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   229,    29,    30,    31,   149,   118,   225,
     155,   119,    32,   246,   199,   126,    33,    34,    35,    36,
     100,   131,    37,    38,    39,    66,    84,    67,    68,   145,
     106,   141,   138,   139,   252,   267,    98,   174,   127,   171,
     216,   273,   254,   271,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     116,   172,   268,   268,   202,   244,    85,   146,    87,   147,
     107,   108,    59,    60,    61,    62,    63,    82,   241,   203,
     107,   269,   150,   151,   152,   153,    82,    83,   143,    64,
     143,    46,    65,   258,   193,   158,   132,   177,   144,    49,
     217,   175,   133,   134,   135,   136,   107,   182,    44,   109,
     285,    45,   270,   270,   154,   186,   110,   111,   112,   109,
     113,   114,   115,   194,    50,   107,   110,   111,   184,    56,
     113,   185,   115,    47,   195,    48,   233,   218,   219,   220,
     221,    51,   107,   206,   208,   109,    41,    52,    42,    43,
      53,    54,   110,   111,   125,    55,   113,    58,   115,    57,
      69,    75,    70,   107,   109,    71,    72,    76,    73,    74,
     230,   110,   111,   205,    77,   113,    78,   115,   107,   212,
      79,   109,    80,    86,    81,   264,   265,    82,   110,   111,
     207,   255,   113,    88,   115,   107,    89,    90,    91,    92,
      93,    94,   109,    95,    96,   248,    97,   107,   251,   110,
     111,   247,   286,   113,   122,   115,   120,   109,    99,   104,
     105,   107,   123,   124,   110,   111,   250,   128,   113,   129,
     115,   107,   275,     5,   109,   117,   279,   281,   251,   121,
     130,   110,   111,   278,   137,   113,   109,   115,   140,   143,
     148,   156,   157,   110,   111,   280,   159,   113,   293,   115,
     109,   173,   179,   178,   183,   187,   188,   110,   111,   292,
     109,   113,   189,   115,   190,     2,   192,   110,   111,     3,
       4,   113,   196,   115,   197,     5,     6,     7,     8,     9,
      10,    11,   198,   160,   211,    12,    13,    14,   200,   201,
     215,   204,    15,    16,   161,   162,   163,   164,   165,   166,
     167,   168,    17,   228,   213,   223,   263,   226,   227,   231,
     224,   232,   169,   237,   236,   234,   170,   161,   162,   163,
     164,   165,   166,   167,   168,   161,   162,   163,   164,   165,
     166,   167,   168,   238,   239,   169,   240,   242,   243,   170,
     245,   249,   257,   169,   253,   256,   259,   170,    59,    60,
      61,    62,    63,   260,   261,   262,   266,   272,   274,   276,
     277,   283,   287,   291,   294,   101,   296,   295,   102,   297,
     191,   176,   210,   222,   142,   103,   282,   181,   214,   288,
     235,   180,   289,   209,   290,   284
};

static const yytype_int16 yycheck[] =
{
      88,   126,    11,    11,    47,   230,    65,   114,    67,   116,
      17,    18,    48,    49,    50,    51,    52,    19,   227,    62,
      17,    29,    23,    24,    25,    26,    19,    29,    19,    65,
      19,    65,    68,   242,    17,   123,    29,   131,    29,     3,
      29,   129,   101,   102,   103,   104,    17,   141,     6,    56,
     275,     9,    61,    61,    55,   143,    63,    64,    65,    56,
      67,    68,    69,    46,    30,    17,    63,    64,    65,    38,
      67,    68,    69,     7,    57,     9,   201,   184,   185,   186,
     187,     3,    17,   171,   172,    56,     6,     3,     8,     9,
       3,     3,    63,    64,    65,     3,    67,    65,    69,    32,
       3,     3,    65,    17,    56,     9,    65,     3,    65,    65,
     198,    63,    64,    65,    32,    67,    65,    69,    17,   178,
      39,    56,    65,    32,    35,   250,   251,    19,    63,    64,
      65,   238,    67,    17,    69,    17,    17,    65,    36,     3,
       3,    65,    56,    31,    67,   233,    33,    17,   236,    63,
      64,    65,   277,    67,     3,    69,    36,    56,    65,    65,
      65,    17,    17,    30,    63,    64,    65,     3,    67,    40,
      69,    17,   260,    10,    56,    65,   264,   265,   266,    65,
      19,    63,    64,    65,    53,    67,    56,    69,    19,    19,
      19,    65,    17,    63,    64,    65,     6,    67,   286,    69,
      56,    34,    54,    65,    18,    65,    18,    63,    64,    65,
      56,    67,    18,    69,    18,     0,    18,    63,    64,     4,
       5,    67,    17,    69,    65,    10,    11,    12,    13,    14,
      15,    16,    19,    29,     3,    20,    21,    22,    65,    65,
      59,    46,    27,    28,    40,    41,    42,    43,    44,    45,
      46,    47,    37,    19,    65,     3,    29,    56,    65,    18,
      63,     3,    58,    60,    36,    29,    62,    40,    41,    42,
      43,    44,    45,    46,    47,    40,    41,    42,    43,    44,
      45,    46,    47,    65,    18,    58,    18,    65,    18,    62,
      19,    65,    18,    58,    65,    57,     3,    62,    48,    49,
      50,    51,    52,    17,     3,    29,    34,    19,     3,    65,
      65,    65,    29,    18,    65,    65,    29,   291,    68,    65,
     148,   130,   176,   191,   107,    82,   266,   140,   181,   282,
     209,   139,   283,   173,   284,   272
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    72,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    85,
      86,    87,    93,    97,    98,    99,   100,   103,   104,   105,
     125,     6,     8,     9,     6,     9,    65,     7,     9,     3,
      30,     3,     3,     3,     3,     3,    38,    32,    65,    48,
      49,    50,    51,    52,    65,    68,   106,   108,   109,     3,
      65,     9,    65,    65,    65,     3,     3,    32,    65,    39,
      65,    35,    19,    29,   107,   107,    32,   107,    17,    17,
      65,    36,     3,     3,    65,    31,    67,    33,   117,    65,
     101,    65,    68,   108,    65,    65,   111,    17,    18,    56,
      63,    64,    65,    67,    68,    69,    96,    65,    89,    92,
      36,    65,     3,    17,    30,    65,    96,   119,     3,    40,
      19,   102,    29,   107,   107,   107,   107,    53,   113,   114,
      19,   112,   104,    19,    29,   110,   110,   110,    19,    88,
      23,    24,    25,    26,    55,    91,    65,    17,    96,     6,
      29,    40,    41,    42,    43,    44,    45,    46,    47,    58,
      62,   120,   120,    34,   118,    96,   101,   117,    65,    54,
     113,   111,   117,    18,    65,    68,    96,    65,    18,    18,
      18,    89,    18,    17,    46,    57,    17,    65,    19,    95,
      65,    65,    47,    62,    46,    65,    96,    65,    96,   119,
     102,     3,   107,    65,   112,    59,   121,    29,   110,   110,
     110,   110,    88,     3,    63,    90,    56,    65,    19,    84,
      96,    18,     3,   120,    29,   118,    36,    60,    65,    18,
      18,    84,    65,    18,    95,    19,    94,    65,    96,    65,
      65,    96,   115,    65,   123,   110,    57,    18,    84,     3,
      17,     3,    29,    29,   120,   120,    34,   116,    11,    29,
      61,   124,    19,   122,     3,    96,    65,    65,    65,    96,
      65,    96,   115,    65,   123,    95,   120,    29,   116,   124,
     122,    18,    65,    96,    65,    94,    29,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    83,    84,    84,    85,    86,    87,    88,    88,
      89,    89,    89,    89,    89,    90,    91,    91,    91,    91,
      91,    92,    93,    94,    94,    95,    95,    96,    96,    96,
      96,    96,    96,    97,    98,    99,   100,   101,   102,   102,
     103,   104,   105,   106,   106,   106,   106,   107,   107,   107,
     107,   107,   108,   108,   108,   108,   108,   109,   109,   109,
     109,   109,   110,   110,   110,   110,   110,   111,   112,   112,
     113,   113,   114,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   124,   125
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
       1,     1,     3,     1,     5,     1,     7,     3,     0,     3,
       1,     7,     2,     2,     2,     4,     2,     0,     3,     5,
       3,     3,     5,     7,     3,     5,     5,     1,     1,     1,
       1,     1,     0,     3,     5,     3,     3,     2,     0,     3,
       0,     2,     6,     3,     3,     3,     3,     5,     5,     7,
       0,     3,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     2,     0,     4,     0,     3,     2,
       4,     0,     1,     1,     8
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
#line 189 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1478 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 194 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1486 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 199 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 205 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1502 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 211 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1510 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 217 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1518 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 223 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1527 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 229 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1535 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 235 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1544 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 243 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1554 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 249 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1564 "yacc_sql.tab.c"
    break;

  case 34: /* id_list: COMMA ID id_list  */
#line 257 "yacc_sql.y"
                {
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
		}
#line 1572 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 263 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1581 "yacc_sql.tab.c"
    break;

  case 36: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 270 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;//"show_index";
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1590 "yacc_sql.tab.c"
    break;

  case 37: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 277 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1602 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 287 "yacc_sql.y"
                                   {    }
#line 1608 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 291 "yacc_sql.y"
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
#line 1623 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 301 "yacc_sql.y"
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
#line 1638 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 311 "yacc_sql.y"
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
#line 1653 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NOT NULL_T  */
#line 321 "yacc_sql.y"
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
#line 1668 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 331 "yacc_sql.y"
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
#line 1683 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 343 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1689 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 346 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1695 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 347 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1701 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 348 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1707 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 349 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1713 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 350 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1719 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 354 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1728 "yacc_sql.tab.c"
    break;

  case 52: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE record_list SEMICOLON  */
#line 362 "yacc_sql.y"
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
#line 1747 "yacc_sql.tab.c"
    break;

  case 54: /* record_list: COMMA LBRACE value value_list RBRACE record_list  */
#line 378 "yacc_sql.y"
                                                          {

	}
#line 1755 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: %empty  */
#line 383 "yacc_sql.y"
                {
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->row_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1764 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 387 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
#line 1772 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 392 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
	}
#line 1780 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 395 "yacc_sql.y"
            {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
	}
#line 1788 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 398 "yacc_sql.y"
          {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
	}
#line 1797 "yacc_sql.tab.c"
    break;

  case 60: /* value: DATE_STR  */
#line 402 "yacc_sql.y"
                   {
        value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1805 "yacc_sql.tab.c"
    break;

  case 61: /* value: NULL_T  */
#line 405 "yacc_sql.y"
                 {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1813 "yacc_sql.tab.c"
    break;

  case 62: /* value: LBRACE sub_select RBRACE  */
#line 408 "yacc_sql.y"
                                   {
		value_init_select(&CONTEXT->values[CONTEXT->value_length++], &CONTEXT->selects[CONTEXT->select_length-1]);
		CONTEXT->select_length--;
	}
#line 1822 "yacc_sql.tab.c"
    break;

  case 63: /* delete_begin: DELETE  */
#line 414 "yacc_sql.y"
               {
		CONTEXT->select_length++;
	}
#line 1830 "yacc_sql.tab.c"
    break;

  case 64: /* delete: delete_begin FROM ID where SEMICOLON  */
#line 420 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			
			CONTEXT->condition_length[0] = 0;	
			CONTEXT->select_length = 0;
    }
#line 1844 "yacc_sql.tab.c"
    break;

  case 65: /* update_begin: UPDATE  */
#line 431 "yacc_sql.y"
               {
		CONTEXT->select_length++;
	}
#line 1852 "yacc_sql.tab.c"
    break;

  case 66: /* update: update_begin ID SET update_set updates_sets where SEMICOLON  */
#line 437 "yacc_sql.y"
                {
  			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
  			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), 
						 CONTEXT->conditions[0], CONTEXT->condition_length[0]);

  			CONTEXT->condition_length[0] = 0;
  			CONTEXT->value_length = 0;
			CONTEXT->select_length = 0;
		}
#line 1866 "yacc_sql.tab.c"
    break;

  case 67: /* update_set: ID EQ value  */
#line 449 "yacc_sql.y"
                    {
		updates_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &CONTEXT->values[CONTEXT->value_length - 1]);
	}
#line 1874 "yacc_sql.tab.c"
    break;

  case 69: /* updates_sets: COMMA update_set updates_sets  */
#line 455 "yacc_sql.y"
                                        {
	
	}
#line 1882 "yacc_sql.tab.c"
    break;

  case 70: /* select_begin: SELECT  */
#line 460 "yacc_sql.y"
               {
		CONTEXT->select_length++;
	}
#line 1890 "yacc_sql.tab.c"
    break;

  case 71: /* sub_select: select_begin select_attr FROM rel_name rel_list where order_by  */
#line 465 "yacc_sql.y"
                                                                       {
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->conditions[CONTEXT->select_length-1], CONTEXT->condition_length[CONTEXT->select_length-1]);
	}
#line 1898 "yacc_sql.tab.c"
    break;

  case 72: /* select: sub_select SEMICOLON  */
#line 471 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[0];
			//临时变量清零
			// CONTEXT->condition_length=0;
			// CONTEXT->from_length=0;
			// CONTEXT->select_length=0;
			// CONTEXT->value_length = 0;
			// CONTEXT->join_length = 0;
	}
#line 1913 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: STAR attr_list  */
#line 483 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1923 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: ID attr_list  */
#line 488 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1933 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: ID DOT ID attr_list  */
#line 493 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1943 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: aggr_attr attr_list  */
#line 498 "yacc_sql.y"
                              {

	}
#line 1951 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA ID attr_list  */
#line 504 "yacc_sql.y"
                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 1961 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA ID DOT ID attr_list  */
#line 509 "yacc_sql.y"
                                {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 1971 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA STAR attr_list  */
#line 514 "yacc_sql.y"
                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
    }
#line 1981 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA aggr_attr attr_list  */
#line 519 "yacc_sql.y"
                                    {
	}
#line 1988 "yacc_sql.tab.c"
    break;

  case 82: /* aggr_attr: aggr_type LBRACE ID extra_attr RBRACE  */
#line 523 "yacc_sql.y"
                                               {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, NULL, (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 1998 "yacc_sql.tab.c"
    break;

  case 83: /* aggr_attr: aggr_type LBRACE ID DOT ID extra_attr RBRACE  */
#line 528 "yacc_sql.y"
                                                       {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2008 "yacc_sql.tab.c"
    break;

  case 84: /* aggr_attr: aggr_type LBRACE RBRACE  */
#line 533 "yacc_sql.y"
                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, INVALID, 0, NULL, NULL, NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2018 "yacc_sql.tab.c"
    break;

  case 85: /* aggr_attr: aggr_type LBRACE STAR extra_attr RBRACE  */
#line 538 "yacc_sql.y"
                                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t == COUNT ? COUNT : INVALID, 1, NULL, "*", NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2028 "yacc_sql.tab.c"
    break;

  case 86: /* aggr_attr: aggr_type LBRACE value extra_attr RBRACE  */
#line 543 "yacc_sql.y"
                                                   {
		AggrAttr attr;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggr_init(&attr, CONTEXT->aggr_t, 0, NULL, NULL, value);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2039 "yacc_sql.tab.c"
    break;

  case 87: /* aggr_type: MAX_T  */
#line 551 "yacc_sql.y"
                { CONTEXT->aggr_t = MAX; }
#line 2045 "yacc_sql.tab.c"
    break;

  case 88: /* aggr_type: MIN_T  */
#line 552 "yacc_sql.y"
                { CONTEXT->aggr_t = MIN; }
#line 2051 "yacc_sql.tab.c"
    break;

  case 89: /* aggr_type: AVG_T  */
#line 553 "yacc_sql.y"
                { CONTEXT->aggr_t = AVG; }
#line 2057 "yacc_sql.tab.c"
    break;

  case 90: /* aggr_type: SUM_T  */
#line 554 "yacc_sql.y"
                { CONTEXT->aggr_t = SUM; }
#line 2063 "yacc_sql.tab.c"
    break;

  case 91: /* aggr_type: COUNT_T  */
#line 555 "yacc_sql.y"
                  { CONTEXT->aggr_t = COUNT; }
#line 2069 "yacc_sql.tab.c"
    break;

  case 93: /* extra_attr: COMMA ID extra_attr  */
#line 559 "yacc_sql.y"
                              { CONTEXT->aggr_t = INVALID; }
#line 2075 "yacc_sql.tab.c"
    break;

  case 94: /* extra_attr: COMMA ID DOT ID extra_attr  */
#line 560 "yacc_sql.y"
                                     { CONTEXT->aggr_t = INVALID; }
#line 2081 "yacc_sql.tab.c"
    break;

  case 95: /* extra_attr: COMMA STAR extra_attr  */
#line 561 "yacc_sql.y"
                                { CONTEXT->aggr_t = INVALID; }
#line 2087 "yacc_sql.tab.c"
    break;

  case 96: /* extra_attr: COMMA value extra_attr  */
#line 562 "yacc_sql.y"
                                 { CONTEXT->aggr_t = INVALID; }
#line 2093 "yacc_sql.tab.c"
    break;

  case 97: /* rel_name: ID join_list  */
#line 565 "yacc_sql.y"
                     {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-1].string));
		selects_arrange_relation(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->curr_join_length);
		CONTEXT->curr_join_length=0;
	}
#line 2103 "yacc_sql.tab.c"
    break;

  case 99: /* rel_list: COMMA rel_name rel_list  */
#line 572 "yacc_sql.y"
                              {	
	}
#line 2110 "yacc_sql.tab.c"
    break;

  case 101: /* join_list: inner_join join_list  */
#line 577 "yacc_sql.y"
                               {

	}
#line 2118 "yacc_sql.tab.c"
    break;

  case 102: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 583 "yacc_sql.y"
                                                            {
		selects_append_join_relation(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-3].string));
		selects_append_join_conditions(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->join_conditions[CONTEXT->join_length], CONTEXT->join_conditions_length[CONTEXT->join_length]);
		CONTEXT->join_length++;
		CONTEXT->curr_join_length++;
	}
#line 2129 "yacc_sql.tab.c"
    break;

  case 103: /* join_condition: ID comOp value  */
#line 590 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2144 "yacc_sql.tab.c"
    break;

  case 104: /* join_condition: value comOp value  */
#line 600 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2157 "yacc_sql.tab.c"
    break;

  case 105: /* join_condition: ID comOp ID  */
#line 608 "yacc_sql.y"
                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2172 "yacc_sql.tab.c"
    break;

  case 106: /* join_condition: value comOp ID  */
#line 618 "yacc_sql.y"
                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2186 "yacc_sql.tab.c"
    break;

  case 107: /* join_condition: ID DOT ID comOp value  */
#line 627 "yacc_sql.y"
                            {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2200 "yacc_sql.tab.c"
    break;

  case 108: /* join_condition: value comOp ID DOT ID  */
#line 636 "yacc_sql.y"
                                {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
#line 2215 "yacc_sql.tab.c"
    break;

  case 109: /* join_condition: ID DOT ID comOp ID DOT ID  */
#line 646 "yacc_sql.y"
                                {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
#line 2230 "yacc_sql.tab.c"
    break;

  case 111: /* join_condition_list: AND join_condition join_condition_list  */
#line 659 "yacc_sql.y"
                                                {
	}
#line 2237 "yacc_sql.tab.c"
    break;

  case 113: /* where: WHERE condition condition_list  */
#line 664 "yacc_sql.y"
                                     {	
	}
#line 2244 "yacc_sql.tab.c"
    break;

  case 115: /* condition_list: AND condition condition_list  */
#line 669 "yacc_sql.y"
                                   {
	}
#line 2251 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID comOp value  */
#line 673 "yacc_sql.y"
                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
#line 2266 "yacc_sql.tab.c"
    break;

  case 117: /* condition: value comOp value  */
#line 683 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
#line 2279 "yacc_sql.tab.c"
    break;

  case 118: /* condition: ID comOp ID  */
#line 691 "yacc_sql.y"
                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);

		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
#line 2295 "yacc_sql.tab.c"
    break;

  case 119: /* condition: value comOp ID  */
#line 702 "yacc_sql.y"
                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
#line 2309 "yacc_sql.tab.c"
    break;

  case 120: /* condition: ID DOT ID comOp value  */
#line 711 "yacc_sql.y"
                            {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
#line 2323 "yacc_sql.tab.c"
    break;

  case 121: /* condition: value comOp ID DOT ID  */
#line 720 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2338 "yacc_sql.tab.c"
    break;

  case 122: /* condition: ID DOT ID comOp ID DOT ID  */
#line 730 "yacc_sql.y"
                                {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2353 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: EQ  */
#line 742 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->select_length-1] = EQUAL_TO; }
#line 2359 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: LT  */
#line 743 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = LESS_THAN; }
#line 2365 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: GT  */
#line 744 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_THAN; }
#line 2371 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: LE  */
#line 745 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = LESS_EQUAL; }
#line 2377 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: GE  */
#line 746 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_EQUAL; }
#line 2383 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: NE  */
#line 747 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = NOT_EQUAL; }
#line 2389 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: LK  */
#line 748 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->select_length-1] = LIKE; }
#line 2395 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: NOT LK  */
#line 749 "yacc_sql.y"
                 { CONTEXT->comp[CONTEXT->select_length-1] = NOT_LIKE; }
#line 2401 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: IS  */
#line 750 "yacc_sql.y"
              { CONTEXT->comp[CONTEXT->select_length-1] = IS_OP; }
#line 2407 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: IS NOT  */
#line 751 "yacc_sql.y"
                 { CONTEXT->comp[CONTEXT->select_length-1] = IS_NOT_OP; }
#line 2413 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: IN  */
#line 752 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->select_length-1] = IN_OP; }
#line 2419 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: NOT IN  */
#line 753 "yacc_sql.y"
                 { CONTEXT->comp[CONTEXT->select_length-1] = NOT_IN_OP; }
#line 2425 "yacc_sql.tab.c"
    break;

  case 136: /* order_by: ORDER BY order_attr order_attr_list  */
#line 757 "yacc_sql.y"
                                              {
	}
#line 2432 "yacc_sql.tab.c"
    break;

  case 138: /* order_attr_list: COMMA order_attr order_attr_list  */
#line 762 "yacc_sql.y"
                                           {
	}
#line 2439 "yacc_sql.tab.c"
    break;

  case 139: /* order_attr: ID direction  */
#line 767 "yacc_sql.y"
                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order_attr(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
#line 2450 "yacc_sql.tab.c"
    break;

  case 140: /* order_attr: ID DOT ID direction  */
#line 773 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order_attr(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
#line 2461 "yacc_sql.tab.c"
    break;

  case 141: /* direction: %empty  */
#line 781 "yacc_sql.y"
                    {
		CONTEXT->is_desc = 0;
	}
#line 2469 "yacc_sql.tab.c"
    break;

  case 142: /* direction: ASC  */
#line 784 "yacc_sql.y"
              {
		CONTEXT->is_desc = 0;
	}
#line 2477 "yacc_sql.tab.c"
    break;

  case 143: /* direction: DESC  */
#line 787 "yacc_sql.y"
               {
		CONTEXT->is_desc = 1;
	}
#line 2485 "yacc_sql.tab.c"
    break;

  case 144: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 793 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2494 "yacc_sql.tab.c"
    break;


#line 2498 "yacc_sql.tab.c"

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

#line 798 "yacc_sql.y"

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
