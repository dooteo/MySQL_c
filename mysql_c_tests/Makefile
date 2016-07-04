
CC = gcc
CFLAGS = -Wall
INCLUDES = -I/usr/local/include/mysql
LIBS = -L/usr/local/lib/mysql -lmysqlclient
MKDIR = mkdir -p

# Needed directories
OBJDIR = obj

SRCS = main.c mysql.c db_tb_lang.c
OBJS =  $(SRCS:.c=.o)
# Objects list with pathname included
OBJS_wPATH = $(patsubst %,$(OBJDIR)/%,$(OBJS)) 

#$(SRCS:.c=.o)

TARGET = mysql_test

.PHONY: all clean clearscreen checkdirs

all: clearscreen checkdirs $(TARGET)


# Note: -o $@ says to put the output of the compilation in the file
#            named on the left side of the :
#        $< is the first item in the dependencies list
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) -o $@ $<


# Note: $^ is right side of the :
${TARGET}: $(OBJS_wPATH)
	$(CC) $(CFLAGS) -o $(TARGET) $^  $(LIBS) 


# Check needed directories exists, otherwise create them
checkdirs:
	if [ ! -d "$(OBJDIR)" ]; then $(MKDIR) $(OBJDIR); fi

# Clear terminal or console screen 
clearscreen:
	clear

# Delete objects and compiled files
clean:
	rm -f $(TARGET) $(OBJDIR)/*
