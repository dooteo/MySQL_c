/* ***************************************************
* File: db_tb_lang.h
* Description:
*	This file contains class to be used with 'c_lang' table
*
*
*************************************************** */

#include <iostream>

// ---- MySQL/MariaDB headers ----
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>


class TB_Lang {

public:
	// ---- Contructors ----
	TB_Lang();
	~TB_Lang();

	// ---- Methods ----
	unsigned int create(sql::Connection *dbconn, const char *isocode, const char *engname, 
										const char *origname, unsigned int active);
	unsigned int read_by_isocode(sql::Connection *dbconn, const char *isocode);
	unsigned int remove(sql::Connection *dbconn, const char *isocode);
	unsigned int edit();

private:
	// ---- "c_lang" Table fields ---
	unsigned int active;
	unsigned long long id;
	char isocode[10];
	char engname[45];
	char origname[45];

	// ---- Auxiliar variables ----
	unsigned int status;
	unsigned int rows_affected;

	// ---- To be used as Prepared Statement ----
	unsigned long num_rows;
	sql::PreparedStatement  *prep_stmt;
	sql::ResultSet *pResultSet;

};

