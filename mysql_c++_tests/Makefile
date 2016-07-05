CC = g++
CPPFLAGS = -Wall
INCS = -I/usr/include/cppconn  
LIBS = -L/usr/lib -lmysqlcppconn

TARGET = main

.PHONY: all clean cleanscreen

all:
	$(CC) $(CPPFLAGS) $(INCS) $(LIBS) -o $(TARGET) main.cpp


cleanscreen:
	clear
clean:
	rm -f $(TARGET) *.o
