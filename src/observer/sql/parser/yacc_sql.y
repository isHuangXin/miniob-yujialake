
%{

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

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
		UNIQUE
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
		DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
		NOT
		LK
		MAX_T
		MIN_T
		AVG_T
		SUM_T
		COUNT_T
		INNER
		JOIN
		TEXT_T
		NULL_T
		NULLABLE
		IS
		ORDER
		BY
		ASC
		IN

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> DATE_STR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| show_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 0);
			create_index_add(&CONTEXT->ssql->sstr.create_index, $7);
		}
	| CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 1);
			create_index_add(&CONTEXT->ssql->sstr.create_index, $8);
		}
    ;
id_list:
	| COMMA ID id_list
		{
			create_index_add(&CONTEXT->ssql->sstr.create_index, $2);
		}
	;
drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
show_index:			/*show index 语句的语法解析树*/
	SHOW INDEX FROM ID SEMICOLON
		{
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;//"show_index";
			show_index_init(&CONTEXT->ssql->sstr.show_index, $4);
		}
	;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, $4, 0);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
		CONTEXT->value_length++;
	}
	| ID_get type LBRACE number RBRACE NULLABLE {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, $4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
		CONTEXT->value_length++;
	}
    | ID_get type {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, $2 == TEXTS ? 4096 : 4, 0);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
	| ID_get type NOT NULL_T {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, $2 == TEXTS ? 4096 : 4, 0);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
	| ID_get type NULLABLE {
		AttrInfo attribute;
		attr_info_init(&attribute, CONTEXT->id, $2, $2 == TEXTS ? 4096 : 4, 1);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
		// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
		// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
		CONTEXT->value_length++;
	}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
       | TEXT_T { $$=TEXTS; }
	   | DATE_T { $$=DATES; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE record_list SEMICOLON {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
		inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
		//临时变量清零
		CONTEXT->row_num=0;
		CONTEXT->value_length=0;
    }
record_list:
    /* empty */ 
	| COMMA LBRACE value value_list RBRACE record_list{

	}
	;
value_list:
    /* empty */ {
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->row_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
    ;
value:
    NUMBER {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
	}
    | FLOAT {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
	}
    | SSS {
		$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
	}
	| DATE_STR {
        value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1);
    } 
	| NULL_T {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	} 
	| LBRACE sub_select RBRACE {
		value_init_select(&CONTEXT->values[CONTEXT->value_length++], &CONTEXT->selects[CONTEXT->select_length-1]);
		CONTEXT->select_length--;
	}
    ;
delete_begin:
	DELETE {
		CONTEXT->select_length++;
	}
	;
delete:		/*  delete 语句的语法解析树*/
    delete_begin FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			
			CONTEXT->condition_length[0] = 0;	
			CONTEXT->select_length = 0;
    }
    ;
update_begin:
	UPDATE {
		CONTEXT->select_length++;
	}
	;
update:			/*  update 语句的语法解析树*/
	update_begin ID SET update_set updates_sets where SEMICOLON
		{
  			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
  			updates_init(&CONTEXT->ssql->sstr.update, $2, 
						 CONTEXT->conditions[0], CONTEXT->condition_length[0]);

  			CONTEXT->condition_length[0] = 0;
  			CONTEXT->value_length = 0;
			CONTEXT->select_length = 0;
		}
	;

update_set:
	ID EQ value {
		updates_append(&CONTEXT->ssql->sstr.update, $1, &CONTEXT->values[CONTEXT->value_length - 1]);
	}
	;

updates_sets:
	| COMMA update_set updates_sets {
	
	}
    ;
select_begin:
	SELECT {
		CONTEXT->select_length++;
	}
	;
sub_select: 
	select_begin select_attr FROM rel_name rel_list where order_by {
			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->conditions[CONTEXT->select_length-1], CONTEXT->condition_length[CONTEXT->select_length-1]);
	}
	;
select:				/*  select 语句的语法解析树*/
    sub_select SEMICOLON
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
	;
select_attr:
    STAR attr_list {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
    | ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
  	| ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
	| aggr_attr attr_list {

	}
    ;
attr_list:
    /* empty */
    | COMMA ID attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
    | COMMA ID DOT ID attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	| COMMA STAR attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
    }
	| COMMA aggr_attr attr_list {
	}
  	;
aggr_attr:
	 aggr_type LBRACE ID extra_attr RBRACE {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, NULL, $3, NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	| aggr_type LBRACE ID DOT ID extra_attr RBRACE {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t, 1, $3, $5, NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	| aggr_type LBRACE RBRACE {
		AggrAttr attr;
		relation_aggr_init(&attr, INVALID, 0, NULL, NULL, NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	| aggr_type LBRACE STAR extra_attr RBRACE {
		AggrAttr attr;
		relation_aggr_init(&attr, CONTEXT->aggr_t == COUNT ? COUNT : INVALID, 1, NULL, "*", NULL);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	} 
	| aggr_type LBRACE value extra_attr RBRACE {
		AggrAttr attr;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggr_init(&attr, CONTEXT->aggr_t, 0, NULL, NULL, value);
		selects_append_aggr(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
	;
aggr_type:
	  MAX_T { CONTEXT->aggr_t = MAX; }
	| MIN_T { CONTEXT->aggr_t = MIN; }
	| AVG_T { CONTEXT->aggr_t = AVG; }
	| SUM_T { CONTEXT->aggr_t = SUM; }
	| COUNT_T { CONTEXT->aggr_t = COUNT; }
	;
extra_attr:
    /* empty */
	| COMMA ID extra_attr { CONTEXT->aggr_t = INVALID; }
	| COMMA ID DOT ID extra_attr { CONTEXT->aggr_t = INVALID; }
	| COMMA STAR extra_attr { CONTEXT->aggr_t = INVALID; }
	| COMMA value extra_attr { CONTEXT->aggr_t = INVALID; }
  	;
rel_name:
	ID join_list {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], $1);
		selects_arrange_relation(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->curr_join_length);
		CONTEXT->curr_join_length=0;
	}
rel_list:
    /* empty */
    | COMMA rel_name rel_list {	
	}
    ;
join_list:
    /* empty */
	| inner_join join_list {

	}
	;

inner_join:
	INNER JOIN ID ON join_condition join_condition_list {
		selects_append_join_relation(&CONTEXT->selects[CONTEXT->select_length-1], $3);
		selects_append_join_conditions(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->join_conditions[CONTEXT->join_length], CONTEXT->join_conditions_length[CONTEXT->join_length]);
		CONTEXT->join_length++;
		CONTEXT->curr_join_length++;
	};
join_condition:
	ID comOp value {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
	| value comOp value {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
	| ID comOp ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
    | value comOp ID {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
    | ID DOT ID comOp value {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
	}
    | value comOp ID DOT ID	{
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, $3, $5);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
    | ID DOT ID comOp ID DOT ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		RelAttr right_attr;
		relation_attr_init(&right_attr, $5, $7);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->join_conditions[CONTEXT->join_length][CONTEXT->join_conditions_length[CONTEXT->join_length]++] = condition;
    }
    ;
join_condition_list:
    /* empty */
	| AND join_condition join_condition_list{
	}
	;
where:
    /* empty */ 
    | WHERE condition condition_list {	
	}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
	}
    ;
condition:
    ID comOp value {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
	| value comOp value {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
	| ID comOp ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);

		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
    | value comOp ID {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
    | ID DOT ID comOp value {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
    | value comOp ID DOT ID {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, $3, $5);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
    | ID DOT ID comOp ID DOT ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		RelAttr right_attr;
		relation_attr_init(&right_attr, $5, $7);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
    ;
comOp:
  	  EQ { CONTEXT->comp[CONTEXT->select_length-1] = EQUAL_TO; }
    | LT { CONTEXT->comp[CONTEXT->select_length-1] = LESS_THAN; }
    | GT { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_THAN; }
    | LE { CONTEXT->comp[CONTEXT->select_length-1] = LESS_EQUAL; }
    | GE { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_EQUAL; }
    | NE { CONTEXT->comp[CONTEXT->select_length-1] = NOT_EQUAL; }
	| LK { CONTEXT->comp[CONTEXT->select_length-1] = LIKE; }
	| NOT LK { CONTEXT->comp[CONTEXT->select_length-1] = NOT_LIKE; }
	| IS  { CONTEXT->comp[CONTEXT->select_length-1] = IS_OP; }
	| IS NOT { CONTEXT->comp[CONTEXT->select_length-1] = IS_NOT_OP; }
	| IN { CONTEXT->comp[CONTEXT->select_length-1] = IN_OP; }
	| NOT IN { CONTEXT->comp[CONTEXT->select_length-1] = NOT_IN_OP; }
    ;
order_by:
	/* empty */
	| ORDER BY order_attr order_attr_list {
	}
	;
order_attr_list:
	/* empty */
	| COMMA order_attr order_attr_list {
	}
	;

order_attr:
	ID direction {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		selects_append_order_attr(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
	| ID DOT ID direction {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_order_attr(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->is_desc);
		CONTEXT->is_desc = 0;
	}
	;
direction:
	/* empty */ {
		CONTEXT->is_desc = 0;
	}
	| ASC {
		CONTEXT->is_desc = 0;
	} 
	| DESC {
		CONTEXT->is_desc = 1;
	}
	;
load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
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
