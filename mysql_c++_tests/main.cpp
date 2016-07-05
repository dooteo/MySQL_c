#include "main.h"

using namespace std;

int main(int argc, char *argv[]) {

	cout << endl;
	cout << "Running 'SELECT * FROM c_lang;'" << endl;

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		// ---- Create a connection ----
		driver = get_driver_instance();
		con = driver->connect("localhost", "dooteo", "popo");

		// ---- Connect to the MySQL test database ----
		con->setSchema("c_test01");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT isocode FROM c_lang;");
		while (res->next()) {

			// getString("field_name") == access column data by alias or column name
			cout << "\t... MySQL replies: " << res->getString("isocode") << endl;

			// getString(col_number) == access column fata by numeric offset, 1 is the first column
			cout << "\t... MySQL says it again: " << res->getString(1) << endl;
		}

		// Free allocated memory
		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	return (RETURN_SUCCESS);
}
