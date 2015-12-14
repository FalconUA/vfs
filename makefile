TARGET = demo
CC = g++
CFLAGS =
HEADERS = \
		  virtualfs.h \
		  virtualos.h \
		  vfs/directory.h \
		  vfs/file.h \
		  vfs/filesystem.h \
		  vos/operatingsystem.h \
		  vos/utility.h \
		  utility/cat.h \
		  utility/cd.h \
		  utility/ls.h \
		  utility/mkdir.h \
		  uitlity/pwd.h \
		  utility/shell.h \
		  utility/help.h \
		  utility/rm.h \
		  utility/touch.h \
		  lazy_initialize.h \


OBJECTS = \
		  vfs/directory.o \
		  vfs/file.o \
		  vfs/filesystem.o \
		  vos/operatingsystem.o \

DEMO = main.o

demo: $(OBJECTS) $(DEMO)
	$(CC) $(CFLAGS) $(OBJECTS) $(DEMO) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $<

clean:
	rm -r *.o $(TARGET)
	

