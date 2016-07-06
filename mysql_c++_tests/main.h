#ifndef DOUS_MAIN_H
#define DOUS_MAIN_H

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "db_tb_lang.h"

#define RETURN_SUCCESS 0

#define MYSQL_HOST "localhost"
#define MYSQL_USER "dooteo"
#define MYSQL_PASS "popo"
#define MYSQL_DB "c_test01"

#endif
