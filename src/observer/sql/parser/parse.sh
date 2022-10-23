#!/usr/bin/env sh

flex --header-file=lex.yy.h lex_sql.l
bison -t -d -b yacc_sql yacc_sql.y
