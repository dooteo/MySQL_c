#include "db_tb_lang.h"
/*
// http://dev.mysql.com/doc/refman/5.6/en/c-api-prepared-statement-type-codes.html
Input Variable C Type	buffer_type Value		SQL Type of Destination Value
---------------------  	-----------------		-----------------------------
signed char				MYSQL_TYPE_TINY			TINYINT
short int				MYSQL_TYPE_SHORT		SMALLINT
int						MYSQL_TYPE_LONG			INT
long long int			MYSQL_TYPE_LONGLONG		BIGINT
float					MYSQL_TYPE_FLOAT		FLOAT
double					MYSQL_TYPE_DOUBLE		DOUBLE
MYSQL_TIME				MYSQL_TYPE_TIME			TIME
MYSQL_TIME				MYSQL_TYPE_DATE			DATE
MYSQL_TIME				MYSQL_TYPE_DATETIME		DATETIME
MYSQL_TIME				MYSQL_TYPE_TIMESTAMP	TIMESTAMP
char[]					MYSQL_TYPE_STRING		TEXT, CHAR, VARCHAR
char[]					MYSQL_TYPE_BLOB			BLOB, BINARY, VARBINARY
 						MYSQL_TYPE_NULL			NULL
---------------------  	-----------------		-----------------------------
*/

// Bibliography:
// http://lgallardo.com/2011/06/23/sentencias-preparadas-de-mysql-en-c-ejemplo-completo/
// http://dev.mysql.com/doc/refman/5.7/en/mysql-stmt-execute.html
   

unsigned int db_tb_lang_insert(MYSQL *dbconn, char *isocode, char *engname, 
							char *origname, unsigned int active, my_ulonglong *lastId) {

	int status = SUCCESS;
	#define INSERT_SQLQUERY "INSERT INTO c_lang \
								(isocode, engname, origname, active) \
								VALUES (?, ?, ?, ?)"
	# define ISO_STRING_SIZE 10
	# define LANG_STRING_SIZE 45

	MYSQL_STMT *stmt;
	// ---- Bind variable
	MYSQL_BIND param[4];
	my_ulonglong  aux; // To check if INSERT was succesfully completed and get last inserted ID

	int param_count;
	// ---- Vars for SQL QUERY Parameters
	unsigned int myActive;
	char myIsoCode[ISO_STRING_SIZE];
	char myEngName[LANG_STRING_SIZE];
	char myOrigName[LANG_STRING_SIZE];
	unsigned long str_len1, str_len2, str_len3;

	stmt = mysql_stmt_init(dbconn);
	if (stmt == NULL) {
		fprintf(stderr, "Could not initialize statement handler. Out of memory\n");
		return(199);
	}

	// Prepare the statement
	if (mysql_stmt_prepare(stmt, INSERT_SQLQUERY, strlen(INSERT_SQLQUERY)) != 0) {
		fprintf(stderr, "Could not prepare statement: %s\n", mysql_stmt_error(stmt));
		return(200);
	}

	// Get the parameter count from the statement
	// Not really needed ¿?
	param_count= mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in INSERT: %d\n", param_count);
	if (param_count != 4) { // validate parameter count
		fprintf(stderr, " invalid parameter count returned by MySQL\n");
		exit(1);
	}

	// ---- Bind the data for all 4 parameters ----
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer      = (char *) &myIsoCode;
	param[0].buffer_length = ISO_STRING_SIZE;
	param[0].is_null     = 0;
	param[0].length      = &str_len1;

	param[1].buffer_type = MYSQL_TYPE_STRING;
	param[1].buffer      = (char *) &myEngName;
	param[1].buffer_length = LANG_STRING_SIZE;
	param[1].is_null     = 0;
	param[1].length      = &str_len2;

	param[2].buffer_type = MYSQL_TYPE_STRING;
	param[2].buffer      = (char *) &myOrigName;
	param[2].buffer_length = LANG_STRING_SIZE;
	param[2].is_null     = 0;
	param[2].length      = &str_len3;

	param[3].buffer_type = MYSQL_TYPE_TINY;
	param[3].buffer      = (int *) &myActive;
	param[3].is_null     = 0; // This field was set to not be NULL
	param[3].length      = 0;

	// Bind param structure to statement
	if (mysql_stmt_bind_param(stmt, param) != 0) {
		fprintf(stderr, "Could not bind parameters: %s\n", mysql_stmt_error(stmt));
		return(201);
	}

	// ---- Specify the data values for the first row ----
	strncpy(myIsoCode, isocode, ISO_STRING_SIZE); // string
	strncpy(myEngName, engname, LANG_STRING_SIZE);
	strncpy(myOrigName, origname, LANG_STRING_SIZE);
	myActive = active;

	str_len1 = strlen(myIsoCode);
	str_len2 = strlen(myEngName);
	str_len3 = strlen(myOrigName);

	// ---- Execute the INSERT statement ----
	if (mysql_stmt_execute(stmt)) {
		fprintf(stderr, " mysql_stmt_execute(), 1 failed\n%s\n", mysql_stmt_error(stmt));
		exit(1);
	}

	// ---- Get the number of affected rows
	aux= mysql_stmt_affected_rows(stmt);
	fprintf(stdout, " total affected rows (insert 1): %lu\n", (unsigned long) aux);
	if (aux != 1) { // validate affected rows
		fprintf(stderr, " invalid affected rows by MySQL\n");
		exit(1);
	}

	aux = mysql_stmt_insert_id(stmt); // To get AUTO_INCREMENT column last ID 
	if (! aux) { // aux == 0 means no ID!
		*lastId = aux;
	} else {
		*lastId = 0;
	}

	// ---- Close Query ----
	// Deallocate result set
	mysql_stmt_free_result(stmt); 

	// Close the statement
	mysql_stmt_close(stmt);

	return (status);
}

unsigned int db_tb_lang_delete(MYSQL *dbconn, char *isocode) {

	int status = SUCCESS;
	#define DELETE_SQLQUERY "DELETE FROM c_lang WHERE (isocode = ?)"
	#define ISO_STRING_SIZE 10

	MYSQL_STMT *stmt;
	// ---- Bind variable
	MYSQL_BIND param[1];
	my_ulonglong  aux; // To check if DELETE was succesfully completed and get last inserted ID

	int param_count;
	// ---- Vars for SQL QUERY Parameters
	char myIsoCode[ISO_STRING_SIZE];
	unsigned long str_len1;

	// ---- Init Prepared Statement
	stmt = mysql_stmt_init(dbconn);
	if (stmt == NULL) {
		fprintf(stderr, "Could not initialize statement handler. Out of memory\n");
		return(199);
	}

	// Prepare the statement
	if (mysql_stmt_prepare(stmt, DELETE_SQLQUERY, strlen(DELETE_SQLQUERY)) != 0) {
		fprintf(stderr, "Could not prepare statement: %s\n", mysql_stmt_error(stmt));
		return(200);
	}

	// Get the parameter count from the statement
	// Not really needed ¿?
	param_count= mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in DELETE: %d\n", param_count);
	if (param_count != 1) { // validate parameter count
		fprintf(stderr, " invalid parameter count returned by MySQL\n");
		exit(1);
	}

	// ---- Bind the data for a parameter ----
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer      = (char *) &myIsoCode;
	param[0].buffer_length = ISO_STRING_SIZE;
	param[0].is_null     = 0;
	param[0].length      = &str_len1;

	// ---- Bind param structure to statement
	if (mysql_stmt_bind_param(stmt, param) != 0) {
		fprintf(stderr, "Could not bind parameters: %s\n", mysql_stmt_error(stmt));
		return(201);
	}

	// ---- Specify the data values for the first row ----
	strncpy(myIsoCode, isocode, ISO_STRING_SIZE); 
	str_len1 = strlen(myIsoCode);

	// ---- Execute the DELETE statement ----
	if (mysql_stmt_execute(stmt)) {
		fprintf(stderr, " mysql_stmt_execute(), 1 failed\n%s\n", mysql_stmt_error(stmt));
		exit(1);
	}

	// ---- Get the number of affected rows
	aux = mysql_stmt_affected_rows(stmt);
	fprintf(stdout, " total deleted rows: %lu\n", (unsigned long) aux);
	if (aux != 1) { // validate affected rows
		fprintf(stderr, " invalid affected rows by MySQL\n");
		exit(1);
	}

	// ---- Close Query ----
	// Deallocate result set
	mysql_stmt_free_result(stmt); 

	// Close the statement
	mysql_stmt_close(stmt);

	return (status);
}
unsigned int db_tb_lang_get(MYSQL *dbconn, char *isocode, Lang **my_lang) {

	#define STRING_SIZE 45

	int status = SUCCESS;
	// Note: even 'isocode' field is a STRING TYPE, don't put quotes 
	// 		before and after ? symbol
	char *sqlquery = "SELECT id, engname, origname FROM c_lang WHERE (isocode = ?)";

	MYSQL_STMT *stmt;
	// Bind variables
	MYSQL_BIND param[1], result[3];
	my_bool is_null[1]; // my_bool type defined at mysql.h

	// Vars to store result set's fields in
	unsigned int myId;
	char myLang[STRING_SIZE];
	char myEngName[STRING_SIZE];
	char myOrigName[STRING_SIZE];
	
	unsigned long str_len1, str_len2;
	int param_count;
	Lang *new_node = malloc(sizeof(Lang));

	stmt = mysql_stmt_init(dbconn);
	if (stmt == NULL) {
		fprintf(stderr, "Could not initialize statement handler. Out of memory\n");
		return(199);
	}

	// Prepare the statement
	if (mysql_stmt_prepare(stmt, sqlquery, strlen(sqlquery)) != 0) {
		fprintf(stderr, "Could not prepare statement: %s\n", mysql_stmt_error(stmt));
		return(200);
	}

	param_count = mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

	// Initialize the result column structures
	memset (param, 0, sizeof(param)); // zero the structures
	memset (result, 0, sizeof(result)); // zero the structures

	// Init param structure
	// Select
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer      = (char *) &myLang; // maybe, you can use (void *)
	param[0].buffer_length = STRING_SIZE;
	param[0].is_null     = 0;
	param[0].length      = &str_len1;


	// Prepare MYSQL_BIND struct to store row's fields in at later mysql_stmt_execute() call
	result[0].buffer_type = MYSQL_TYPE_LONG;
	result[0].buffer      = (void *) &myId;
	result[0].is_unsigned = 0;
	result[0].is_null     = &is_null[0];
	result[0].length      = 0;

	result[1].buffer_type = MYSQL_TYPE_STRING;
	result[1].buffer      = (char *) &myEngName; 
	result[1].buffer_length = STRING_SIZE;
	result[1].is_null     = 0;
	result[1].length      = &str_len2;

	result[2].buffer_type = MYSQL_TYPE_STRING;
	result[2].buffer      = (char *) &myOrigName; 
	result[2].buffer_length = STRING_SIZE;
	result[2].is_null     = 0;
	result[2].length      = &str_len2;

	// Bind param structure to statement
	if (mysql_stmt_bind_param(stmt, param) != 0) {
		fprintf(stderr, "Could not bind parameters");
		return(201);
	}

	// Bind result
	if (mysql_stmt_bind_result(stmt, result) != 0) {
		fprintf(stderr, "Could not bind results");
		return(202);
	}

	// Set bind parameters
	strncpy(myLang, isocode, STRING_SIZE); /* string  */
	str_len1= strlen(myLang);
	printf("myLang = %s\n", myLang);

	// Execute!!
	if (mysql_stmt_execute(stmt) != 0) {
		fprintf(stderr, "Could not execute statement\n");
		return(203);
	}

	// Note: It is unnecessary to call mysql_stmt_store_result() after 
	// 		executing an SQL statement that does not produce a result set
	// 		That's why we don't call it in _insert_ and _delete_ functions.
	// See:  
	//		http://dev.mysql.com/doc/refman/5.7/en/mysql-stmt-store-result.html

	// mysql_stmt_store_result() gets whole result set from MySQL server,
	// so set is stored into client.
	if (mysql_stmt_store_result(stmt) != 0) {
		fprintf(stderr, "Could not buffer result set");
		return(204);
	}

	// Fetch result set
	if ( mysql_stmt_fetch(stmt) != 0) {
		fprintf(stderr, "Could not fetch: %d: %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
	} else {
		// Store fields values into function's params vars
		new_node->id = myId;
		strncpy(new_node->engname, myEngName, 45);
		strncpy(new_node->origname, myOrigName, 45);
	}
	*my_lang = new_node;

	// Deallocate result set
	mysql_stmt_free_result(stmt); 

	// Close the statement
	mysql_stmt_close(stmt);

	return (status);
}

/* unsigned int db_tb_lang_fetch_rows(MYSQL *dbconn, char *isocode, unsigned int *id, \
						char **engname, char **origname) {
*/
unsigned int db_tb_lang_fetch_rows(MYSQL *dbconn, char *isocode, Lang **my_lang) {

	#define STRING_SIZE 45

	int status = SUCCESS;
	// Note: even 'isocode' field is a STRING TYPE, don't put quotes 
	// 		before and after ? symbol
	char *sqlquery = "SELECT id, engname, origname FROM c_lang WHERE (isocode = ?)";

	MYSQL_STMT *stmt;
	// Bind variables
	MYSQL_BIND param[1], result[3];
	my_bool is_null[1]; // my_bool type defined at mysql.h

	// Vars to store result set's fields in
	unsigned int myId;
	char myLang[STRING_SIZE];
	char myEngName[STRING_SIZE];
	char myOrigName[STRING_SIZE];
	
	unsigned long str_len1, str_len2;
	int param_count;

	unsigned int row;
	my_ulonglong total_rows = 0;
	Lang *cur_node = NULL;

	stmt = mysql_stmt_init(dbconn);
	if (stmt == NULL) {
		fprintf(stderr, "Could not initialize statement handler. Out of memory\n");
		return(199);
	}

	// Prepare the statement
	if (mysql_stmt_prepare(stmt, sqlquery, strlen(sqlquery)) != 0) {
		fprintf(stderr, "Could not prepare statement: %s\n", mysql_stmt_error(stmt));
		return(200);
	}

	param_count = mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

	// Initialize the result column structures
	memset (param, 0, sizeof(param)); // zero the structures
	memset (result, 0, sizeof(result)); // zero the structures

	// Init param structure
	// Select
	param[0].buffer_type = MYSQL_TYPE_STRING;
	param[0].buffer      = (char *) &myLang; // maybe, you can use (void *)
	param[0].buffer_length = STRING_SIZE;
	param[0].is_null     = 0;
	param[0].length      = &str_len1;


	// Prepare MYSQL_BIND struct to store row's fields in at later mysql_stmt_execute() call
	result[0].buffer_type = MYSQL_TYPE_LONG;
	result[0].buffer      = (void *) &myId;
	result[0].is_unsigned = 0;
	result[0].is_null     = &is_null[0];
	result[0].length      = 0;

	result[1].buffer_type = MYSQL_TYPE_STRING;
	result[1].buffer      = (char *) &myEngName; 
	result[1].buffer_length = STRING_SIZE;
	result[1].is_null     = 0;
	result[1].length      = &str_len2;

	result[2].buffer_type = MYSQL_TYPE_STRING;
	result[2].buffer      = (char *) &myOrigName; 
	result[2].buffer_length = STRING_SIZE;
	result[2].is_null     = 0;
	result[2].length      = &str_len2;

	// Bind param structure to statement
	if (mysql_stmt_bind_param(stmt, param) != 0) {
		fprintf(stderr, "Could not bind parameters");
		return(201);
	}

	// Bind result
	if (mysql_stmt_bind_result(stmt, result) != 0) {
		fprintf(stderr, "Could not bind results");
		return(202);
	}

	// Set bind parameters
	strncpy(myLang, isocode, STRING_SIZE); /* string  */
	str_len1= strlen(myLang);
	printf("myLang = %s\n", myLang);

	// ---- Execute Prepared Statement !!
	if (mysql_stmt_execute(stmt) != 0) {
		fprintf(stderr, "Could not execute statement\n");
		return(203);
	}

	// Note: mysql_stmt_store_result() must be used after mysql_stmt_bind_result() and 
	//	 mysql_stmt_execute() functions, but before than mysql_stmt_fetch().
	//   If it os used between mysql_stmt_bind_result() and mysql_stmt_execute(), it causes 
	//   an error 'Commands out of sync'.

	status = mysql_stmt_store_result(stmt);
	if (status != SUCCESS) {
		fprintf(stderr, "Could not store results: %d. %s\n", mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
		return(202);
	}

	// Note2: If you use mysql_stmt_store_result(), mysql_stmt_num_rows()
	//    may be called immediately.

	total_rows = mysql_stmt_num_rows(stmt);
	printf("Rows total: %llu\n", total_rows);


	// Note 3: We gonna use an array of Lang struct. I'm realize using a 
	// list of struct will be another way. But current option is more simple.

	// Check there is more than zero rows in result set
	if (total_rows == 0) {
		*my_lang = NULL;
		return (status);
	}
	cur_node = malloc(total_rows * sizeof(Lang));
	*my_lang = cur_node;

	if (cur_node == NULL) {
		fprintf(stderr, "Could not allocate memory for Lang struct list.\n");
		exit(1);
	} else {
		printf("Main: %p. Cur: %p", my_lang, cur_node);
	}

	for(row = 0; row < total_rows; row++) {
		mysql_stmt_fetch(stmt);
		
		cur_node->id = myId;
		strncpy(cur_node->isocode, myLang, 10);
		strncpy(cur_node->engname, myEngName, 45);
		strncpy(cur_node->origname, myOrigName, 45);

		if ( row < (total_rows -1) ) {
			cur_node->is_end = 0;
			cur_node++;
		} else {
			cur_node->is_end = 1;
		}

		printf("  %p \t%u\t | \t%s\t | \t%s \t\n", cur_node, myId ,myEngName, myOrigName);
		printf(" --------------------------------------------------------------------- \n");	
	}
	
	// Deallocate result set
	mysql_stmt_free_result(stmt); 

	// Close the statement
	mysql_stmt_close(stmt);

	return (status);
}

