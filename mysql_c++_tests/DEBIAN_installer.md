#How to install required packs in Debian GNU/Linux

As superuser (U know, 'root') install **libmysqlcppconn-dev** package:

	apt-get install libmysqlcppconn-dev libmysqlclient18

*Doubts thoughts of mine: Sounds weird, but MySQL connector calls to libmysqlclient library (which is used at C lang)... so maybe better to devel with C instead of with C++.*

