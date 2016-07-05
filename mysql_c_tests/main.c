#include "main.h"

int main (int argc, char *argv[]) {

	unsigned int status = 0, isLoop;
	MYSQL *connect;

	my_ulonglong lastID;
	Lang *my_lang = NULL;
	Lang *cur_lang = NULL;

	status = db_open(&connect, DB_SERVER, DB_USER, DB_PASSWD, DB_NAME);
	if (status > SUCCESS) {
		db_print_error(connect);
		exit (EXIT_FAILURE);
	}

	printf("\t---- Connection succeeded ----\n");

	status = db_tb_lang_get(connect, "es", &my_lang);
	

	if (status == SUCCESS ) {
		printf("ID: %u, English Name: %s, Original Name: %s\n", my_lang->id, my_lang->engname, my_lang->origname);

	} else {
		printf("Status: %u\n", status);
	}

	free(my_lang);

	status = db_tb_lang_insert(connect, "fr", "French", "Francoise", 1, &lastID);
	if (status == SUCCESS ) {
		printf("Portuguese inserted. ID: %llu\n", lastID);

	} else {
		printf("Status: %u\n", status);
	}
	status = db_tb_lang_fetch_rows(connect, "sfr", &my_lang);
	cur_lang = my_lang;

	// Now, let's print whole struct array to check it's okey
	printf(" -----------main: %p  cur: %p ---------------------------- \n", my_lang, cur_lang);

	// Check Lang struct pointer has some rows from result set 
	if (my_lang != NULL) {
		isLoop = 1;
	} else {
		isLoop = 0;
	}

	while (isLoop) {
		printf(" %p \t%u\t | \t%s\t | \t%s \t\n", cur_lang, cur_lang->id, cur_lang->engname, cur_lang->origname);
		printf(" --------------------------------------------------------------------- \n");

		if (cur_lang->is_end == 1) {
			isLoop = 0;
		} else {
			cur_lang++;	
		}
	}

	// Free previously allocated memory in db_tb_lang_fetch_rows() for Lang struct array
	free(my_lang);

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

