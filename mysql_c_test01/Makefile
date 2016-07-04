CC = gcc
INCLUDES = -I/usr/local/include/mysql
LIBS = -L/usr/local/lib/mysql -lmysqlclient
TARGET = mysql_test

.PHONY: all clean

all: ${TARGET}

main.o: main.c main.h
	$(CC) -c $(INCLUDES) main.c

${TARGET}: main.o 
	$(CC) -o $(TARGET) main.o $(LIBS) 

clean:
	rm -f $(TARGET) *.o 
