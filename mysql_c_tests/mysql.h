/* ****************************
*  File: mysql.h
*  Description: main functions to use with MySQL
*************************
*  Developer: Iñaki Larrañaga Murgoitio <dooteo@zundan.com>, 2016
*************************
* License: GPL v3 or newer
*********************** */

#ifndef DOUS_MYSQL_H
#define DOUS_MYSQL_H

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include "global_consts.h"

unsigned int db_open(MYSQL **dbconn, char *dbserver, char *dbuser, char *dbpsswd, char *dbname);
unsigned int db_close(MYSQL *dbconn);
int db_query(MYSQL *dbconn, char *sqlquery);

void db_print_rows(MYSQL *dbconn);
void db_print_cols(MYSQL_ROW row, unsigned int num_cols, char sep);
void db_print_hinterline(unsigned int max_cols, unsigned long *len, char node, char line);

void db_print_error(MYSQL *dbconn);

#endif
