#include "main.h"

int main (int argc, char *argv[]) {

	unsigned int status = 0;
	MYSQL *connect;
	// ---- Params to store row's fields in
	unsigned int id;
	//char *isocode;
	char *engname;
	char *origname;
	my_ulonglong lastID;

	status = db_open(&connect, DB_SERVER, DB_USER, DB_PASSWD, DB_NAME);
	if (status > SUCCESS) {
		db_print_error(connect);
		exit (1);
	}

	printf("\t---- Connection succeeded ----\n");

	status = db_tb_lang_get(connect, "es", &id, &engname, &origname);

	if (status == SUCCESS ) {
		printf("ID: %u, English Name: %s, Original Name: %s\n", id, engname, origname);

	} else {
		printf("Status: %u\n", status);
	}

	status = db_tb_lang_insert(connect, "fr", "French", "Francoise", 1, &lastID);
	if (status == SUCCESS ) {
		printf("Portuguese inserted. ID: %llu\n", lastID);

	} else {
		printf("Status: %u\n", status);
	}
	status = db_tb_lang_fetch_rows(connect, "fr", &id, &engname, &origname);

	status = db_tb_lang_delete(connect, "pt");
	if (status == SUCCESS ) {
		printf("Portuguese deleted.\n");

	} else {
		printf("Status: %u\n", status);
	}


	status = db_close(connect);
	if (status > SUCCESS) {
		db_print_error(connect);
	}

	return (0);
}

