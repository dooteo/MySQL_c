/* ****************************
*  File: db-tb_lang.h
*  Description: functions to handle 'c_lang' table.
*************************
*  Developer: Iñaki Larrañaga Murgoitio <dooteo@zundan.com>, 2016
*************************
* License: GPL v3 or newer
*********************** */

#ifndef DOUS_DB_TB_ADMIN_H
#define DOUS_DB_TB_ADMIN_H

#include <stdlib.h>
#include <string.h>

#include "mysql.h"
#include "global_consts.h"

typedef struct tb_lang {
	unsigned int is_end;
	unsigned int id;
	char isocode[10];
	char engname[45];
	char origname[45];

	//struct tb_lang *next;
} Lang;

unsigned int db_tb_lang_insert(MYSQL *dbconn, char *isocode, char *engname, 
						char *origname, unsigned int active, my_ulonglong *lastId);

unsigned int db_tb_lang_delete(MYSQL *dbconn, char *isocode);

unsigned int db_tb_lang_get(MYSQL *dbconn, char *isocode, Lang **my_lang);

unsigned int db_tb_lang_fetch_rows(MYSQL *dbconn, char *isocode, Lang **my_lang);

#endif
