CC=gcc
CINCLUDE= -I. -I/usr/include/mysql
MYOPTIMIZE = -g -O2 -fomit-frame-pointer -march=pentium4
CFLAGS=-Wall $(MYOPTIMIZE) $(CINCLUDE)
SQLLINK= -L/usr/lib/mysql -lmysqlclient
all : acwk


acwk : wk.c acctsql.o TCPIP.o error.o tools.o util.o
	$(CC) $(CFLAGS) $(SQLLINK) -o acwk wk.c error.o TCPIP.o tools.o acctsql.o util.o
acctsql:
	$(CC) $(CFLAGS) -c acctsql.c
TCPIP:
	$(CC) $(CFLAGS) -c TCPIP.c
error:
	$(CC) $(CFLAGS) -c error.c
tools:
	$(CC) $(CFLAGS) -c tools.c
util:
	$(CC) $(CFLAGS) -c util.c
clean :
	rm -f acwk *.o *~


