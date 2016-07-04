#include "mysql.h"

unsigned int db_open(MYSQL **dbconn, char *dbserver, char *dbuser, char *dbpsswd, char *dbname) {

	*dbconn = mysql_init(NULL);

	if (! *dbconn) {
		return (ERR_MYSQL_INIT);
	}

	*dbconn = mysql_real_connect(*dbconn, dbserver, dbuser, dbpsswd, dbname, 0, NULL, 0);
	if (! *dbconn) {
		db_close(*dbconn);
		return (ERR_MYSQL_REAL_CONN);
	}

	return (SUCCESS);
}

unsigned int db_close(MYSQL *dbconn) {
	mysql_close(dbconn);

	if (! dbconn) {
		return (ERR_MYSQL_NOT_CLOSED_CONN);
	}

	return (SUCCESS);
}

int db_query(MYSQL *dbconn, char *sqlquery) {
	int status;

	status = mysql_query(dbconn, sqlquery);
	if (status > SUCCESS) {
		db_print_error(dbconn);
	}

	return (status);
}

void db_print_rows(MYSQL *dbconn) {

	unsigned int numrows;
	unsigned int num_cols;
	unsigned long *lengths;

	MYSQL_RES *res_set;
	MYSQL_ROW row;

	res_set = mysql_store_result(dbconn);
	if (! res_set) {
		db_print_error(dbconn);
		return;
	}

	numrows = mysql_num_rows(res_set);
	if (numrows < 1) {
		return;
	}

	while ( (row = mysql_fetch_row(res_set)) !=NULL )	{ 
		num_cols = mysql_num_fields(res_set);
		lengths = mysql_fetch_lengths(res_set);

		db_print_hinterline(num_cols, lengths, '+', '-');
		db_print_cols(row, num_cols, '|');
		db_print_hinterline(num_cols, lengths, '+', '-');

	}

	mysql_free_result(res_set);
	res_set = NULL; // Set res as default NULL
}

void db_print_cols(MYSQL_ROW row, unsigned int num_cols, char sep){
	unsigned int col;

	for (col = 0; col < num_cols; col++) {
		printf("%c %s ", sep, row[col]);
	}
	printf("%c\n", sep);
}

void db_print_hinterline(unsigned int max_cols, unsigned long *len, char node, char line) {
	unsigned int col, j;

	for (col = 0; col < max_cols; col++) {
		printf("%c", node);
		for (j = 0; j < (len[col] + 2); j++) {
			printf("%c", line);
		}
	}
	printf("%c\n", node);
}

void db_print_error(MYSQL *dbconn) {

	printf("Error [%d]: %s\n", mysql_errno(dbconn), mysql_error(dbconn));
}
