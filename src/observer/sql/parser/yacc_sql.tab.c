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
  size_t selects_num;
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
  YYSYMBOL_internal_select_attr = 102,     /* internal_select_attr  */
  YYSYMBOL_internal_attr_list = 103,       /* internal_attr_list  */
  YYSYMBOL_internal_aggr_attr = 104,       /* internal_aggr_attr  */
  YYSYMBOL_select_attr = 105,              /* select_attr  */
  YYSYMBOL_attr_list = 106,                /* attr_list  */
  YYSYMBOL_aggr_attr = 107,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 108,                /* aggr_type  */
  YYSYMBOL_extra_attr = 109,               /* extra_attr  */
  YYSYMBOL_rel_name = 110,                 /* rel_name  */
  YYSYMBOL_rel_list = 111,                 /* rel_list  */
  YYSYMBOL_join_list = 112,                /* join_list  */
  YYSYMBOL_inner_join = 113,               /* inner_join  */
  YYSYMBOL_join_condition = 114,           /* join_condition  */
  YYSYMBOL_join_condition_list = 115,      /* join_condition_list  */
  YYSYMBOL_where = 116,                    /* where  */
  YYSYMBOL_condition_list = 117,           /* condition_list  */
  YYSYMBOL_condition = 118,                /* condition  */
  YYSYMBOL_comOp = 119,                    /* comOp  */
  YYSYMBOL_order_by = 120,                 /* order_by  */
  YYSYMBOL_order_attr_list = 121,          /* order_attr_list  */
  YYSYMBOL_order_attr = 122,               /* order_attr  */
  YYSYMBOL_direction = 123,                /* direction  */
  YYSYMBOL_load_data = 124                 /* load_data  */
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
#define YYLAST   376

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  331

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
       0,   161,   161,   163,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   188,   193,   198,   204,   210,   216,   222,   228,
     234,   241,   247,   254,   255,   261,   268,   275,   284,   286,
     290,   300,   310,   320,   330,   342,   345,   346,   347,   348,
     349,   352,   361,   375,   377,   382,   386,   391,   394,   397,
     401,   404,   409,   429,   440,   443,   450,   451,   457,   474,
     496,   501,   506,   511,   516,   518,   525,   532,   537,   543,
     548,   553,   558,   563,   573,   578,   583,   588,   592,   594,
     601,   608,   613,   618,   623,   628,   633,   638,   646,   647,
     648,   649,   650,   652,   654,   655,   656,   657,   661,   666,
     668,   672,   674,   679,   686,   696,   704,   714,   723,   732,
     742,   753,   755,   759,   761,   765,   767,   772,   793,   813,
     833,   855,   876,   897,   919,   920,   921,   922,   923,   924,
     925,   926,   928,   930,   934,   936,   941,   947,   955,   958,
     961,   966
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
  "update_set", "updates_sets", "internal_select", "select",
  "internal_select_attr", "internal_attr_list", "internal_aggr_attr",
  "select_attr", "attr_list", "aggr_attr", "aggr_type", "extra_attr",
  "rel_name", "rel_list", "join_list", "inner_join", "join_condition",
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

#define YYPACT_NINF (-218)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -218,   125,  -218,    48,    43,    56,   -52,   102,    10,    18,
      37,   -39,    70,    75,    78,    86,    87,     2,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,    30,    89,    35,
      38,    46,  -218,  -218,  -218,  -218,  -218,    -5,    93,    90,
      93,   104,   121,   123,   100,  -218,    79,    85,   107,  -218,
    -218,  -218,  -218,  -218,   118,   141,    95,   132,   158,   166,
      67,   106,  -218,  -218,   108,  -218,    20,  -218,  -218,   109,
     140,   143,   110,   111,   114,   144,   117,  -218,  -218,    -1,
      93,    93,    93,   134,   182,  -218,  -218,  -218,  -218,     8,
    -218,   184,  -218,   184,   197,   168,   -33,   201,   165,   187,
     177,  -218,   189,    -4,   145,   195,   149,  -218,  -218,  -218,
    -218,   161,  -218,   134,   108,   143,   192,   152,   199,   213,
     218,  -218,    88,   181,   289,   185,  -218,     9,   110,   143,
     212,   114,   219,  -218,  -218,  -218,  -218,  -218,    -7,   221,
     175,    93,   186,  -218,   182,   190,    17,   184,   184,   184,
    -218,  -218,  -218,   232,   188,  -218,  -218,  -218,  -218,  -218,
    -218,   210,  -218,   206,   215,   -33,  -218,   243,  -218,  -218,
     187,   258,   202,   189,   261,   203,   207,  -218,   209,   256,
    -218,   240,  -218,   222,   281,   227,  -218,  -218,  -218,   267,
      88,   275,   289,  -218,  -218,  -218,   265,  -218,   185,   115,
    -218,  -218,   297,  -218,  -218,  -218,   284,  -218,   256,   239,
     291,   224,   247,  -218,   184,  -218,   232,   293,   233,   254,
    -218,    26,    93,   288,   302,   308,  -218,   270,   319,   256,
     335,   200,   289,   305,     5,   321,  -218,  -218,   324,   339,
     314,  -218,  -218,   280,  -218,  -218,   282,   147,  -218,    29,
    -218,   342,  -218,  -218,   283,   242,   251,   224,  -218,  -218,
     285,  -218,  -218,   247,  -218,    88,  -218,   286,    93,   182,
      39,    93,    93,  -218,    51,   184,   184,  -218,   289,  -218,
    -218,   322,  -218,   305,     6,   321,   232,  -218,  -218,   143,
     290,  -218,  -218,  -218,   292,   330,   334,   337,   260,   294,
    -218,  -218,  -218,   341,   343,    93,   184,  -218,  -218,  -218,
     328,  -218,  -218,   293,  -218,  -218,   344,   296,  -218,  -218,
    -218
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
       0,     0,    98,    99,   100,   101,   102,    88,    88,     0,
      88,     0,     0,     0,     0,    24,     0,     0,     0,    25,
      26,    27,    23,    22,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    84,     0,    87,     0,    30,    29,     0,
       0,   123,     0,     0,     0,     0,     0,    28,    35,    88,
      88,    88,    88,   111,   109,    95,    61,    57,    58,   103,
      59,   103,    60,   103,     0,     0,     0,     0,     0,    66,
       0,    51,    38,     0,     0,     0,     0,    89,    91,    92,
      86,     0,   108,   111,     0,   123,     0,     0,     0,     0,
       0,    36,     0,     0,     0,   125,    62,     0,     0,   123,
       0,     0,     0,    46,    47,    48,    50,    49,    42,     0,
       0,    88,     0,   112,   109,   142,   103,   103,   103,   103,
      93,    96,    97,    55,     0,   134,   135,   136,   137,   138,
     139,     0,   140,     0,     0,     0,   124,     0,    64,    65,
      66,     0,     0,    38,     0,     0,     0,    44,     0,    33,
      90,     0,   110,     0,     0,     0,   104,   106,   107,     0,
       0,     0,     0,   141,   129,   127,   130,   128,   125,     0,
      67,    63,     0,    39,    37,    45,     0,    43,    33,     0,
       0,     0,     0,    69,   103,    94,    55,    53,     0,     0,
     126,    88,    88,     0,    74,     0,   151,    40,     0,    33,
       0,     0,     0,   121,   148,   144,   105,    56,     0,     0,
       0,   131,   132,     0,    71,    70,     0,     0,    73,     0,
      41,     0,    34,    31,     0,     0,     0,     0,   113,   150,
       0,   149,   146,     0,   143,     0,    52,     0,    88,   109,
      88,    88,    88,    81,   103,   103,   103,    32,     0,   116,
     114,   117,   115,   121,   148,   144,    55,   133,    72,   123,
       0,    75,    77,    78,     0,     0,     0,     0,     0,     0,
     122,   147,   145,     0,     0,    88,   103,    79,    82,    83,
       0,   118,   119,    53,    68,    76,     0,     0,    54,    80,
     120
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -207,  -218,  -218,  -218,   170,   223,  -218,
    -218,  -218,  -218,    40,  -217,   -73,  -218,  -218,   228,   191,
    -218,  -218,  -218,  -218,  -218,  -218,   -48,   -66,   156,   -96,
     244,  -146,   246,  -218,   103,    74,  -124,   164,   198,  -128,
    -218,    80,   101,    82,  -218
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   220,    29,    30,    31,   142,   112,   216,
     148,   113,    32,   249,   201,   134,    33,    34,   109,   139,
     179,    35,   233,   258,   234,    49,    72,    50,    51,   128,
      94,   125,   122,   123,   243,   268,   107,   176,   135,   173,
     194,   274,   245,   272,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,   155,    75,   103,    91,   129,   174,   130,   192,   247,
     185,   238,    52,    55,    70,   181,   269,   269,    70,   143,
     144,   145,   146,    96,    71,    58,   177,   126,   116,    97,
      98,   133,   262,   100,   270,   102,   126,   127,    95,   186,
      64,   117,   118,   119,   120,    70,   195,   283,    56,    40,
     187,   147,    41,   158,    37,   253,    38,    39,    70,   163,
     196,   197,   198,   199,   178,    96,   271,   271,   300,    57,
     126,    97,    98,    59,   228,   100,    96,   102,    60,   313,
     304,    61,    97,    98,    99,    96,   100,   101,   102,    62,
      63,    97,    98,   284,    65,   100,   285,   102,    66,    67,
     205,   207,    68,   190,    42,    43,    44,    45,    46,    53,
      69,    54,    70,   265,   266,    42,    43,    44,    45,    46,
      47,    76,    74,    48,    77,     2,    78,   226,   246,     3,
       4,    89,    79,   299,    90,     5,     6,     7,     8,     9,
      10,    11,    82,    80,    96,    12,    13,    14,   242,    81,
      97,    98,    15,    16,   100,   251,   102,    83,    84,    85,
     308,    87,    17,    42,    43,    44,    45,    46,    86,    88,
      92,   105,    93,   104,   108,   314,   106,   110,   111,   231,
     114,   115,   232,   254,   255,   132,   286,   121,   305,   306,
     307,   282,   290,   292,   242,    42,    43,    44,    45,    46,
     131,   124,   296,   126,   136,   137,   138,   140,   141,   149,
     164,   280,   150,   151,   281,   152,   159,   160,   182,   175,
     326,   165,   166,   167,   168,   169,   170,   171,   172,   264,
     298,   161,   301,   302,   303,   321,   162,   184,   188,   189,
     165,   166,   167,   168,   169,   170,   171,   172,    96,   193,
     191,   200,   202,   209,    97,    98,   156,   203,   100,   157,
     102,   211,    96,   217,   214,   215,   212,   325,    97,    98,
     204,    96,   100,   218,   102,   219,   221,    97,    98,   206,
      96,   100,   222,   102,   223,   225,    97,    98,   241,    96,
     100,   224,   102,   227,   229,    97,    98,   250,    96,   100,
     236,   102,   237,   239,    97,    98,   289,    96,   100,   240,
     102,   244,   248,    97,    98,   291,    96,   100,   252,   102,
     256,   257,    97,    98,   320,   259,   100,   260,   102,   165,
     166,   167,   168,   169,   170,   171,   172,   261,   263,   267,
     273,   275,   276,   277,   278,   287,   279,   288,   317,   294,
     297,   309,   318,   213,   315,   319,   316,   327,   322,   323,
     330,   324,   329,   328,   183,   235,   180,   310,   154,   153,
     293,   210,   230,   208,   295,   312,   311
};

static const yytype_int16 yycheck[] =
{
      48,   125,    50,    76,    70,   101,   134,   103,   154,   226,
      17,   218,    64,     3,    19,   139,    11,    11,    19,    23,
      24,    25,    26,    56,    29,    64,    17,    19,    29,    62,
      63,    64,   239,    66,    29,    68,    19,    29,    18,    46,
      38,    89,    90,    91,    92,    19,    29,    18,    30,     6,
      57,    55,     9,   126,     6,    29,     8,     9,    19,   132,
     156,   157,   158,   159,   137,    56,    61,    61,    29,    32,
      19,    62,    63,     3,   202,    66,    56,    68,     3,   296,
      29,     3,    62,    63,    64,    56,    66,    67,    68,     3,
       3,    62,    63,    64,    64,    66,    67,    68,     9,    64,
     173,   174,    64,   151,    48,    49,    50,    51,    52,     7,
      64,     9,    19,   241,   242,    48,    49,    50,    51,    52,
      64,    17,    32,    67,     3,     0,     3,   200,   224,     4,
       5,    64,    32,   279,    67,    10,    11,    12,    13,    14,
      15,    16,    35,    64,    56,    20,    21,    22,   221,    64,
      62,    63,    27,    28,    66,   228,    68,    39,    17,    64,
     288,     3,    37,    48,    49,    50,    51,    52,    36,     3,
      64,    31,    64,    64,    64,   299,    33,    66,    64,    64,
      36,    64,    67,   231,   232,    17,   259,    53,   284,   285,
     286,   257,   265,   266,   267,    48,    49,    50,    51,    52,
       3,    19,   275,    19,     3,    40,    19,    30,    19,    64,
      29,    64,    17,    64,    67,    54,    64,    18,     6,    34,
     316,    40,    41,    42,    43,    44,    45,    46,    47,    29,
     278,    18,   280,   281,   282,   308,    18,    18,    17,    64,
      40,    41,    42,    43,    44,    45,    46,    47,    56,    59,
      64,    19,    64,    10,    62,    63,    64,    47,    66,    67,
      68,     3,    56,    56,     3,    62,    64,   315,    62,    63,
      64,    56,    66,    64,    68,    19,    36,    62,    63,    64,
      56,    66,    60,    68,     3,    18,    62,    63,    64,    56,
      66,    64,    68,    18,    29,    62,    63,    64,    56,    66,
       3,    68,    18,    64,    62,    63,    64,    56,    66,    18,
      68,    64,    19,    62,    63,    64,    56,    66,    64,    68,
      32,    19,    62,    63,    64,    17,    66,    57,    68,    40,
      41,    42,    43,    44,    45,    46,    47,    18,     3,    34,
      19,    17,     3,    29,    64,     3,    64,    64,    18,    64,
      64,    29,    18,   183,    64,    18,    64,    29,    64,    18,
      64,    18,    18,   323,   141,   209,   138,   293,   124,   123,
     267,   180,   208,   175,   273,   295,   294
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    37,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    86,    92,    96,    97,   101,   124,     6,     8,     9,
       6,     9,    48,    49,    50,    51,    52,    64,    67,   105,
     107,   108,    64,     7,     9,     3,    30,    32,    64,     3,
       3,     3,     3,     3,    38,    64,     9,    64,    64,    64,
      19,    29,   106,   106,    32,   106,    17,     3,     3,    32,
      64,    64,    35,    39,    17,    64,    36,     3,     3,    64,
      67,   107,    64,    64,   110,    18,    56,    62,    63,    64,
      66,    67,    68,    95,    64,    31,    33,   116,    64,    98,
      66,    64,    88,    91,    36,    64,    29,   106,   106,   106,
     106,    53,   112,   113,    19,   111,    19,    29,   109,   109,
     109,     3,    17,    64,    95,   118,     3,    40,    19,    99,
      30,    19,    87,    23,    24,    25,    26,    55,    90,    64,
      17,    64,    54,   112,   110,   116,    64,    67,    95,    64,
      18,    18,    18,    95,    29,    40,    41,    42,    43,    44,
      45,    46,    47,   119,   119,    34,   117,    17,    95,   100,
      98,   116,     6,    88,    18,    17,    46,    57,    17,    64,
     106,    64,   111,    59,   120,    29,   109,   109,   109,   109,
      19,    94,    64,    47,    64,    95,    64,    95,   118,    10,
      99,     3,    64,    87,     3,    62,    89,    56,    64,    19,
      83,    36,    60,     3,    64,    18,    95,    18,   119,    29,
     117,    64,    67,   102,   104,   108,     3,    18,    83,    64,
      18,    64,    95,   114,    64,   122,   109,    94,    19,    93,
      64,    95,    64,    29,   106,   106,    32,    19,   103,    17,
      57,    18,    83,     3,    29,   119,   119,    34,   115,    11,
      29,    61,   123,    19,   121,    17,     3,    29,    64,    64,
      64,    67,   107,    18,    64,    67,    95,     3,    64,    64,
      95,    64,    95,   114,    64,   122,    95,    64,   106,   111,
      29,   106,   106,   106,    29,   109,   109,   109,   119,    29,
     115,   123,   121,    94,   116,    64,    64,    18,    18,    18,
      64,    95,    64,    18,    18,   106,   109,    29,    93,    18,
      64
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
     104,   104,   104,   104,   105,   105,   105,   105,   106,   106,
     106,   106,   106,   107,   107,   107,   107,   107,   108,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   110,   111,
     111,   112,   112,   113,   114,   114,   114,   114,   114,   114,
     114,   115,   115,   116,   116,   117,   117,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   120,   121,   121,   122,   122,   123,   123,
     123,   124
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
       7,     3,     5,     5,     2,     2,     4,     2,     0,     3,
       5,     3,     3,     5,     7,     3,     5,     5,     1,     1,
       1,     1,     1,     0,     3,     5,     3,     3,     2,     0,
       3,     0,     2,     6,     3,     3,     3,     3,     5,     5,
       7,     0,     3,     0,     3,     0,     3,     3,     3,     3,
       3,     5,     5,     7,     1,     1,     1,     1,     1,     1,
       1,     2,     0,     4,     0,     3,     2,     4,     0,     1,
       1,     8
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
#line 188 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1499 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 193 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1507 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 198 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1515 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 204 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1523 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 210 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1531 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 216 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1539 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 222 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1548 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 228 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1556 "yacc_sql.tab.c"
    break;

  case 30: /* desc_table: DESC ID SEMICOLON  */
#line 234 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1565 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 242 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1575 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 248 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1585 "yacc_sql.tab.c"
    break;

  case 34: /* id_list: COMMA ID id_list  */
#line 256 "yacc_sql.y"
                {
			create_index_add(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
		}
#line 1593 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 262 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1602 "yacc_sql.tab.c"
    break;

  case 36: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 269 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;//"show_index";
			show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
		}
#line 1611 "yacc_sql.tab.c"
    break;

  case 37: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 276 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1623 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 286 "yacc_sql.y"
                                   {    }
#line 1629 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 290 "yacc_sql.y"
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
#line 1644 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 300 "yacc_sql.y"
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
#line 1659 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type  */
#line 310 "yacc_sql.y"
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
#line 1674 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NOT NULL_T  */
#line 320 "yacc_sql.y"
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
#line 1689 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 330 "yacc_sql.y"
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
#line 1704 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 342 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1710 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 345 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1716 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 346 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1722 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 347 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1728 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 348 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1734 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 349 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1740 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 353 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1749 "yacc_sql.tab.c"
    break;

  case 52: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE record_list SEMICOLON  */
#line 361 "yacc_sql.y"
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
#line 1768 "yacc_sql.tab.c"
    break;

  case 54: /* record_list: COMMA LBRACE value value_list RBRACE record_list  */
#line 377 "yacc_sql.y"
                                                          {

	}
#line 1776 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: %empty  */
#line 382 "yacc_sql.y"
                {
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->row_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1785 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 386 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
#line 1793 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 391 "yacc_sql.y"
           {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
	}
#line 1801 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 394 "yacc_sql.y"
            {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
	}
#line 1809 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 397 "yacc_sql.y"
          {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
	}
#line 1818 "yacc_sql.tab.c"
    break;

  case 60: /* value: DATE_STR  */
#line 401 "yacc_sql.y"
                   {
        value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1826 "yacc_sql.tab.c"
    break;

  case 61: /* value: NULL_T  */
#line 404 "yacc_sql.y"
                 {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1834 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 410 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1846 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET update_set updates_sets where SEMICOLON  */
#line 430 "yacc_sql.y"
                {
  			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
  			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), 
						 CONTEXT->conditions, CONTEXT->condition_length);
  			CONTEXT->condition_length = 0;
  			CONTEXT->value_length = 0;
		}
#line 1858 "yacc_sql.tab.c"
    break;

  case 64: /* update_set: ID EQ value  */
#line 440 "yacc_sql.y"
                    {
		updates_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &CONTEXT->values[CONTEXT->value_length - 1]);
	}
#line 1866 "yacc_sql.tab.c"
    break;

  case 65: /* update_set: ID EQ internal_select  */
#line 443 "yacc_sql.y"
                                {
  		value_init_select(&CONTEXT->values[CONTEXT->value_length],
                    &CONTEXT->ssql->selects[CONTEXT->selects_num - 1]);
 		updates_append(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), &CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1876 "yacc_sql.tab.c"
    break;

  case 67: /* updates_sets: COMMA update_set updates_sets  */
#line 451 "yacc_sql.y"
                                        {
	
	}
#line 1884 "yacc_sql.tab.c"
    break;

  case 68: /* internal_select: LBRACE SELECT internal_select_attr FROM ID rel_list where RBRACE  */
#line 457 "yacc_sql.y"
                                                                         {
		int num = CONTEXT->selects_num;
		selects_append_relation(&CONTEXT->ssql->selects[num], (yyvsp[-3].string));
		// selects_reverse_relations(&CONTEXT->ssql->selects[num]);
		selects_append_conditions(&CONTEXT->ssql->selects[num], CONTEXT->conditions, CONTEXT->condition_length);

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
		CONTEXT->selects_num++;
  		CONTEXT->ssql->selects_num = CONTEXT->selects_num;
	}
#line 1903 "yacc_sql.tab.c"
    break;

  case 69: /* select: SELECT select_attr FROM rel_name rel_list where order_by SEMICOLON  */
#line 475 "yacc_sql.y"
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
#line 1926 "yacc_sql.tab.c"
    break;

  case 70: /* internal_select_attr: STAR attr_list  */
#line 496 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
		}
#line 1936 "yacc_sql.tab.c"
    break;

  case 71: /* internal_select_attr: ID attr_list  */
#line 501 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
		}
#line 1946 "yacc_sql.tab.c"
    break;

  case 72: /* internal_select_attr: ID DOT ID attr_list  */
#line 506 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
		}
#line 1956 "yacc_sql.tab.c"
    break;

  case 73: /* internal_select_attr: internal_aggr_attr internal_attr_list  */
#line 511 "yacc_sql.y"
                                                {

	}
#line 1964 "yacc_sql.tab.c"
    break;

  case 75: /* internal_attr_list: COMMA ID attr_list  */
#line 518 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1976 "yacc_sql.tab.c"
    break;

  case 76: /* internal_attr_list: COMMA ID DOT ID attr_list  */
#line 525 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1988 "yacc_sql.tab.c"
    break;

  case 77: /* internal_attr_list: COMMA STAR attr_list  */
#line 532 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
    }
#line 1998 "yacc_sql.tab.c"
    break;

  case 78: /* internal_attr_list: COMMA aggr_attr attr_list  */
#line 537 "yacc_sql.y"
                                   {

	}
#line 2006 "yacc_sql.tab.c"
    break;

  case 79: /* internal_aggr_attr: aggr_type LBRACE ID extra_attr RBRACE  */
#line 543 "yacc_sql.y"
                                               {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, NULL, (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
	  }
#line 2016 "yacc_sql.tab.c"
    break;

  case 80: /* internal_aggr_attr: aggr_type LBRACE ID DOT ID extra_attr RBRACE  */
#line 548 "yacc_sql.y"
                                                       {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
	  }
#line 2026 "yacc_sql.tab.c"
    break;

  case 81: /* internal_aggr_attr: aggr_type LBRACE RBRACE  */
#line 553 "yacc_sql.y"
                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, INVALID, 0, NULL, NULL, NULL);
		selects_append_aggr(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
	  }
#line 2036 "yacc_sql.tab.c"
    break;

  case 82: /* internal_aggr_attr: aggr_type LBRACE STAR extra_attr RBRACE  */
#line 558 "yacc_sql.y"
                                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t == COUNT ? COUNT : INVALID, 1, NULL, "*", NULL);
		selects_append_aggr(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
	  }
#line 2046 "yacc_sql.tab.c"
    break;

  case 83: /* internal_aggr_attr: aggr_type LBRACE value extra_attr RBRACE  */
#line 563 "yacc_sql.y"
                                                   {
		AggrAttr attr;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggr_init(&attr, CONTEXT->aggr_t, 0, NULL, NULL, value);
		selects_append_aggr(&CONTEXT->ssql->selects[CONTEXT->selects_num], &attr);
	}
#line 2057 "yacc_sql.tab.c"
    break;

  case 84: /* select_attr: STAR attr_list  */
#line 573 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2067 "yacc_sql.tab.c"
    break;

  case 85: /* select_attr: ID attr_list  */
#line 578 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2077 "yacc_sql.tab.c"
    break;

  case 86: /* select_attr: ID DOT ID attr_list  */
#line 583 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2087 "yacc_sql.tab.c"
    break;

  case 87: /* select_attr: aggr_attr attr_list  */
#line 588 "yacc_sql.y"
                              {

	}
#line 2095 "yacc_sql.tab.c"
    break;

  case 89: /* attr_list: COMMA ID attr_list  */
#line 594 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2107 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA ID DOT ID attr_list  */
#line 601 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2119 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA STAR attr_list  */
#line 608 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2129 "yacc_sql.tab.c"
    break;

  case 92: /* attr_list: COMMA aggr_attr attr_list  */
#line 613 "yacc_sql.y"
                                   {

	}
#line 2137 "yacc_sql.tab.c"
    break;

  case 93: /* aggr_attr: aggr_type LBRACE ID extra_attr RBRACE  */
#line 618 "yacc_sql.y"
                                               {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, NULL, (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 2147 "yacc_sql.tab.c"
    break;

  case 94: /* aggr_attr: aggr_type LBRACE ID DOT ID extra_attr RBRACE  */
#line 623 "yacc_sql.y"
                                                       {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, (yyvsp[-4].string), (yyvsp[-2].string), NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 2157 "yacc_sql.tab.c"
    break;

  case 95: /* aggr_attr: aggr_type LBRACE RBRACE  */
#line 628 "yacc_sql.y"
                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, INVALID, 0, NULL, NULL, NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 2167 "yacc_sql.tab.c"
    break;

  case 96: /* aggr_attr: aggr_type LBRACE STAR extra_attr RBRACE  */
#line 633 "yacc_sql.y"
                                                  {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t == COUNT ? COUNT : INVALID, 1, NULL, "*", NULL);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 2177 "yacc_sql.tab.c"
    break;

  case 97: /* aggr_attr: aggr_type LBRACE value extra_attr RBRACE  */
#line 638 "yacc_sql.y"
                                                   {
		AggrAttr attr;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggr_init(&attr, CONTEXT->aggr_t, 0, NULL, NULL, value);
		selects_append_aggr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2188 "yacc_sql.tab.c"
    break;

  case 98: /* aggr_type: MAX_T  */
#line 646 "yacc_sql.y"
                { CONTEXT->aggr_t = MAX; }
#line 2194 "yacc_sql.tab.c"
    break;

  case 99: /* aggr_type: MIN_T  */
#line 647 "yacc_sql.y"
                { CONTEXT->aggr_t = MIN; }
#line 2200 "yacc_sql.tab.c"
    break;

  case 100: /* aggr_type: AVG_T  */
#line 648 "yacc_sql.y"
                { CONTEXT->aggr_t = AVG; }
#line 2206 "yacc_sql.tab.c"
    break;

  case 101: /* aggr_type: SUM_T  */
#line 649 "yacc_sql.y"
                { CONTEXT->aggr_t = SUM; }
#line 2212 "yacc_sql.tab.c"
    break;

  case 102: /* aggr_type: COUNT_T  */
#line 650 "yacc_sql.y"
                  { CONTEXT->aggr_t = COUNT; }
#line 2218 "yacc_sql.tab.c"
    break;

  case 104: /* extra_attr: COMMA ID extra_attr  */
#line 654 "yacc_sql.y"
                              { CONTEXT->aggr_t = INVALID; }
#line 2224 "yacc_sql.tab.c"
    break;

  case 105: /* extra_attr: COMMA ID DOT ID extra_attr  */
#line 655 "yacc_sql.y"
                                     { CONTEXT->aggr_t = INVALID; }
#line 2230 "yacc_sql.tab.c"
    break;

  case 106: /* extra_attr: COMMA STAR extra_attr  */
#line 656 "yacc_sql.y"
                                { CONTEXT->aggr_t = INVALID; }
#line 2236 "yacc_sql.tab.c"
    break;

  case 107: /* extra_attr: COMMA value extra_attr  */
#line 657 "yacc_sql.y"
                                 { CONTEXT->aggr_t = INVALID; }
#line 2242 "yacc_sql.tab.c"
    break;

  case 108: /* rel_name: ID join_list  */
#line 661 "yacc_sql.y"
                     {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		selects_arrange_relation(&CONTEXT->ssql->sstr.selection, CONTEXT->curr_join_length);
		CONTEXT->curr_join_length=0;
	}
#line 2252 "yacc_sql.tab.c"
    break;

  case 110: /* rel_list: COMMA rel_name rel_list  */
#line 668 "yacc_sql.y"
                              {	
		// selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
	}
#line 2260 "yacc_sql.tab.c"
    break;

  case 112: /* join_list: inner_join join_list  */
#line 674 "yacc_sql.y"
                              {

	}
#line 2268 "yacc_sql.tab.c"
    break;

  case 113: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 679 "yacc_sql.y"
                                                            {
		selects_append_join_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
		CONTEXT->join_length++;
		CONTEXT->curr_join_length++;
		selects_append_join_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->join_conditions[CONTEXT->join_length-1], CONTEXT->join_conditions_length[CONTEXT->join_length-1]);
	}
#line 2279 "yacc_sql.tab.c"
    break;

  case 114: /* join_condition: ID comOp value  */
#line 686 "yacc_sql.y"
                       {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2294 "yacc_sql.tab.c"
    break;

  case 115: /* join_condition: value comOp value  */
#line 696 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2307 "yacc_sql.tab.c"
    break;

  case 116: /* join_condition: ID comOp ID  */
#line 704 "yacc_sql.y"
                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2322 "yacc_sql.tab.c"
    break;

  case 117: /* join_condition: value comOp ID  */
#line 714 "yacc_sql.y"
                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2336 "yacc_sql.tab.c"
    break;

  case 118: /* join_condition: ID DOT ID comOp value  */
#line 723 "yacc_sql.y"
                            {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
#line 2350 "yacc_sql.tab.c"
    break;

  case 119: /* join_condition: value comOp ID DOT ID  */
#line 732 "yacc_sql.y"
                                {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
#line 2365 "yacc_sql.tab.c"
    break;

  case 120: /* join_condition: ID DOT ID comOp ID DOT ID  */
#line 742 "yacc_sql.y"
                                {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
#line 2380 "yacc_sql.tab.c"
    break;

  case 122: /* join_condition_list: AND join_condition join_condition_list  */
#line 755 "yacc_sql.y"
                                                {

	}
#line 2388 "yacc_sql.tab.c"
    break;

  case 124: /* where: WHERE condition condition_list  */
#line 761 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2396 "yacc_sql.tab.c"
    break;

  case 126: /* condition_list: AND condition condition_list  */
#line 767 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2404 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID comOp value  */
#line 773 "yacc_sql.y"
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
#line 2429 "yacc_sql.tab.c"
    break;

  case 128: /* condition: value comOp value  */
#line 794 "yacc_sql.y"
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
#line 2453 "yacc_sql.tab.c"
    break;

  case 129: /* condition: ID comOp ID  */
#line 814 "yacc_sql.y"
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
#line 2477 "yacc_sql.tab.c"
    break;

  case 130: /* condition: value comOp ID  */
#line 834 "yacc_sql.y"
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
#line 2503 "yacc_sql.tab.c"
    break;

  case 131: /* condition: ID DOT ID comOp value  */
#line 856 "yacc_sql.y"
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
#line 2528 "yacc_sql.tab.c"
    break;

  case 132: /* condition: value comOp ID DOT ID  */
#line 877 "yacc_sql.y"
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
#line 2553 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID DOT ID comOp ID DOT ID  */
#line 898 "yacc_sql.y"
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
#line 2576 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: EQ  */
#line 919 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2582 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: LT  */
#line 920 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2588 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: GT  */
#line 921 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2594 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: LE  */
#line 922 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2600 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: GE  */
#line 923 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2606 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: NE  */
#line 924 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2612 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: LK  */
#line 925 "yacc_sql.y"
             { CONTEXT->comp = LIKE; }
#line 2618 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: NOT LK  */
#line 926 "yacc_sql.y"
                 { CONTEXT->comp = NOT_LIKE; }
#line 2624 "yacc_sql.tab.c"
    break;

  case 143: /* order_by: ORDER BY order_attr order_attr_list  */
#line 930 "yacc_sql.y"
                                              {

	}
#line 2632 "yacc_sql.tab.c"
    break;

  case 145: /* order_attr_list: COMMA order_attr order_attr_list  */
#line 936 "yacc_sql.y"
                                           {

	}
#line 2640 "yacc_sql.tab.c"
    break;

  case 146: /* order_attr: ID direction  */
#line 941 "yacc_sql.y"
                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
#line 2651 "yacc_sql.tab.c"
    break;

  case 147: /* order_attr: ID DOT ID direction  */
#line 947 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
#line 2662 "yacc_sql.tab.c"
    break;

  case 148: /* direction: %empty  */
#line 955 "yacc_sql.y"
                    {
		CONTEXT->is_desc = 0;
	}
#line 2670 "yacc_sql.tab.c"
    break;

  case 149: /* direction: ASC  */
#line 958 "yacc_sql.y"
              {
		CONTEXT->is_desc = 0;
	}
#line 2678 "yacc_sql.tab.c"
    break;

  case 150: /* direction: DESC  */
#line 961 "yacc_sql.y"
               {
		CONTEXT->is_desc = 1;
	}
#line 2686 "yacc_sql.tab.c"
    break;

  case 151: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 967 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2695 "yacc_sql.tab.c"
    break;


#line 2699 "yacc_sql.tab.c"

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

#line 972 "yacc_sql.y"

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
