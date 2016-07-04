/* ****************************
*  File: main.h
*  Description:  _main_ configuration values
*************************
*  Developer: Iñaki Larrañaga Murgoitio <dooteo@zundan.com>, 2016
*************************
* License: GPL v3 or newer
*********************** */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()

// Note: The mysql.h file from the libmysqlclient-dev 
//       Debian package is located at /usr/include/mysql/mysql.h
#include <mysql/mysql.h> 

// ----- Custom headers -----
#include "mysql.h"
#include "db_tb_lang.h"
#include "global_consts.h"



#define DB_SERVER "localhost"
#define DB_USER "dooteo"
#define DB_PASSWD "popo"
#define DB_NAME "c_test01"

#endif
