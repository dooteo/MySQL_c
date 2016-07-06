CC = g++
CPPFLAGS = -Wall
INCLUDES = -I/usr/include/cppconn  
LIBS = -L/usr/lib -lmysqlcppconn
MKDIR = mkdir -p

SRCS = main.cpp db_tb_lang.cpp
OBJS =  $(SRCS:.cpp=.o)
# Objects list with pathname included
OBJS_wPATH = $(patsubst %,$(OBJDIR)/%,$(OBJS)) 

OBJDIR = obj

TARGET = mysql_test

.PHONY: all clean cleanscreen checkdirs purge


all: clearscreen checkdirs $(TARGET)

# Note: -o $@ says to put the output of the compilation in the file
#            named on the left side of the :
#        $< is the first item in the dependencies list
$(OBJDIR)/%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $(INCLUDES) -o $@ $<


# Note: $^ is right side of the :
${TARGET}: $(OBJS_wPATH)
	$(CC) $(CPPFLAGS) -o $(TARGET) $^  $(LIBS) 


# Check needed directories exists, otherwise create them
checkdirs:
	if [ ! -d "$(OBJDIR)" ]; then $(MKDIR) $(OBJDIR); fi

# Clear terminal or console screen 
clearscreen:
	clear

# Delete objects and compiled files
clean:
	rm -f $(TARGET) $(OBJDIR)/*

purge:
	rm -rf $(TARGET) $(OBJDIR)
