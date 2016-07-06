#include "db_tb_lang.h"

using namespace std;

// ---- Contructors ----

TB_Lang::TB_Lang(){
	cout << "TB_Lang object created" << endl;
	num_rows = 0;
	prep_stmt = NULL;
	pResultSet = NULL;
}

TB_Lang::~TB_Lang(){
		cout << "Bye TB_Lang object!" << endl;
}

// ---- Methods ----

// Note: these methods will use Prepared Statement to avoid SQL Injection
// https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-prepared-statements.html
unsigned int TB_Lang::create(sql::Connection *dbconn, const char *isocode, const char *engname, 
											const char *origname, unsigned int active) {

	status = 0;

	prep_stmt = dbconn->prepareStatement("INSERT INTO c_lang (isocode, engname, origname, active)"
										" VALUES (?,?,?,?)");
	
	// Note: be aware about fields number at setString()!
	prep_stmt->setString (1, isocode); 	// 1st field
	prep_stmt->setString (2, engname); 	// 2nd field
	prep_stmt->setString (3, origname); // 3rd field
	prep_stmt->setUInt (4, active);  	// 4th field

	// Note2: executeUpdate() is used when query does not return Result Set, such in 
	//	Insert, Delete and Update type of queries.
	rows_affected = prep_stmt->executeUpdate();

	cout << "[Insert] Rows affected: " << rows_affected << endl;
	return (status);
}


unsigned int TB_Lang::read_by_isocode(sql::Connection *dbconn, const char *isocode){

	status = 0;

	prep_stmt = dbconn->prepareStatement("SELECT * FROM c_lang WHERE (isocode = ?)");
	prep_stmt->setString(1, isocode);
	//prep_stmt->execute();
	pResultSet = prep_stmt->executeQuery();
	
	num_rows = pResultSet->rowsCount();
	cout << "Isocode: " << isocode << "\nTotal rows: " << num_rows << endl;

	while(pResultSet->next()) {
		cout << pResultSet->getString("engname") << " [" << pResultSet->getString("origname") << "]\n";
	}

	return (status);
}
unsigned int TB_Lang::remove(sql::Connection *dbconn, const char *isocode){

	status = 0;

	prep_stmt = dbconn->prepareStatement("DELETE FROM c_lang WHERE (isocode = ?)");
	
	prep_stmt->setString (1, isocode); 	// 1st field
	rows_affected = prep_stmt->executeUpdate();

	cout << "[Delete] Rows affected: " << rows_affected << endl;
	return (status);
}

unsigned int TB_Lang::edit(){
	status = 0;
	cout << "TB_Lang object to update" << endl;
	return (status);
}


