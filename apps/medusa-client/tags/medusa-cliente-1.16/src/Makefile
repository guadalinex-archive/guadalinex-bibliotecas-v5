#
#
# $Id: Makefile 47 2004-08-12 08:58:47Z golan $
# $Author: golan $
# $Date: 2004-08-12 10:58:47 +0200 (Thu, 12 Aug 2004) $
#

CC=gcc
CFLAGS= -O2 -Wall
INC= -I/usr/X11R6/include -I/usr/include/libxml2
LIB= -L/usr/X11R6/lib -L/usr/local/lib -lxml2
LIBS= -lX11 -lXpm

TARGET=mdclient

all: main.o 
	$(CC) $(CFLAGS) $(INC) -c log.c
	$(CC) $(CFLAGS) $(INC) -c conf.c
	$(CC) $(CFLAGS) $(INC) -c window.c
	$(CC) $(CFLAGS) $(INC) -c network.c
	$(CC) $(LIB) $(LIBS) -o $(TARGET) main.o log.o conf.o window.o network.o

clean:
	rm -f $(TARGET)
	rm -f *.o

install: all
	cp $(TARGET) /usr/local/bin/
	cp *.xpm /usr/local/bin

main.o: main.c logo.xpm locked.xpm
	$(CC) $(CFLAGS) $(INC) -c main.c
