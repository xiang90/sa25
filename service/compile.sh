#! /bin/bash

gcc -Wall -g -I. -I/usr/include/mysql -O2 -pipe -fomit-frame-pointer -malign-double -march=pentium4 -c *.c
gcc -Wall -L/usr/lib/mysql -lmysqlclient -o service *.o
