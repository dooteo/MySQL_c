/* ****************************
*  File: error_codes.h
*  Description: constants codes for errors
*************************
*  Developer: Iñaki Larrañaga Murgoitio <dooteo@zundan.com>, 2016
*************************
* License: GPL v3 or newer
*********************** */


#ifndef DOUS_ERROR_CODES_H
#define DOUS_ERROR_CODES_H

#include <stdio.h>

#define SUCCESS 0

// ---- Errors code for MySQL ----
#define ERR_MYSQL_INIT (SUCCESS + 1)
#define ERR_MYSQL_REAL_CONN (ERR_MYSQL_INIT + 1)
#define ERR_MYSQL_NOT_CLOSED_CONN (ERR_MYSQL_REAL_CONN + 1)

#endif
