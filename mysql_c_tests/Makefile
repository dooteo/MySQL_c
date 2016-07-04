
CC = gcc
CFLAGS=-Wall
INCLUDES = -I/usr/local/include/mysql
LIBS = -L/usr/local/lib/mysql -lmysqlclient

OBJDIR=obj

TARGET = mysql_test

.PHONY: all clean clearscreen checkdirs

all: clearscreen checkdirs $(TARGET)


main.o: main.c 	
	clear
	$(CC) $(CFLAGS) -c $(INCLUDES) -o $(OBJDIR)/main.o main.c

mysql.o: mysql.c 
	$(CC) $(CFLAGS) -c $(INCLUDES) -o $(OBJDIR)/mysql.o mysql.c

db_tb_lang.o: db_tb_lang.c
	$(CC) $(CFLAGS) -c $(INCLUDES) -o $(OBJDIR)/db_tb_lang.o db_tb_lang.c

${TARGET}: main.o mysql.o db_tb_lang.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJDIR)/main.o $(OBJDIR)/mysql.o $(OBJDIR)/db_tb_lang.o  $(LIBS) 

checkdirs:
	if [ ! -d "$(OBJDIR)" ]; then mkdir -p $(OBJDIR); fi
clearscreen:
	clear
clean:
	rm -f $(TARGET) $(OBJDIR)/*
