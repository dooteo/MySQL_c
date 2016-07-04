#MySQL C connection
##Test 02
This example uses 'c_test01' as database (see *install_db.sql* file), with 2 tables: *c_lang* and *c_user*.

In this branch, I put connection functions for MariaDB/MySQL into mysql.* files. Access to *c_lang* table can be found into db_tb_lang.* files.

*main.c* just connects to DB and get c_lang tables rows in a very simple way.

##How to import from a SQL file to MariaDB/MySQL

As mysql's 'root' user, run next command:

	mysql -u mysql_root_user -p < install_db.sql 

Or grant username1 permission (into MySQL/MariaDB shell) to create 'c_test01' database:

	MariaDB [(none)]> GRANT ALL PRIVILEGES ON * . * TO 'dooteo'@'localhost';

and then, in a bash shell run a normal user next command:

	$ mysql -u username1 -p < install_db.sql 

And that is!

