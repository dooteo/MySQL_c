#include "main.h"

int main (int argc, char *argv[]) {

	unsigned int col = 0, numrows;
	MYSQL *connect;

	connect = mysql_init(NULL);

	if (!connect) {
		printf("MySQL Initialization failed\n");
		return (1);
	}

	connect = mysql_real_connect(connect, DB_SERVER, DB_USER, DB_PASSWD, DB_NAME, 0, NULL, 0);
	if (! connect) {
		printf("connection failed\n");
		return (1);
	}

	printf("connection Succeeded\n");
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	mysql_query (connect,"select * from c_lang;");

	res_set = mysql_store_result(connect);
	numrows = mysql_num_rows(res_set);

	printf(" ----- ----- ----- ----- Total rows: %d ----- ----- ----- ----- -----\n", numrows);

	while ( (row = mysql_fetch_row(res_set)) !=NULL )	{ 

		printf("  \t%s\t | \t%s\t | \t%s \t\n", row[col] ,row[col+1], row[col+2]);
		printf(" --------------------------------------------------------------------- \n");
	}

	mysql_close(connect);

	return (0);
}

