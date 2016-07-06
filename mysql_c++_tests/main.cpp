#include "main.h"

using namespace std;

int main(int argc, char *argv[]) {

	unsigned int status;
	cout << endl;
	cout << "Running 'SELECT * FROM c_lang;'" << endl;

	try {
		sql::Driver *driver;
		sql::Connection *con;

		TB_Lang my_lang;

		// ---- Create a connection ----
		driver = get_driver_instance();
		con = driver->connect("localhost", "dooteo", "popo");

		// ---- Connect to the MySQL test database ----
		con->setSchema("c_test01");

		//my_lang.read_by_isocode(con, "fr");
		//my_lang.read_by_isocode(con, "es");
		status = my_lang.create(con, "pt_BR", "Brazil Portuguese","Brasileriro", 1);
		cout << "Status: " << status << endl;

		my_lang.read_by_isocode(con, "pt");

		my_lang.remove(con, "fr");

		// ---- Free allocated memory ----

		// Note: no need to remove TB_Lang object, otherwise it'll be
		//	called twice.
		// my_lang.~TB_Lang();

		delete con;

	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		if (e.getErrorCode() == 1047) {
			/*
			Error: 1047 SQLSTATE: 08S01 (ER_UNKNOWN_COM_ERROR)
			Message: Unknown command
			*/
			cout << "\nYour server does not seem to support Prepared Statements at all. ";
			cout << "Perhaps MYSQL < 4.1?" << endl;
		}
		return (EXIT_FAILURE);
	}

	cout << endl;

	return (RETURN_SUCCESS);
}
