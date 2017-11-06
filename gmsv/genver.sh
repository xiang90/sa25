#!/bin/sh
IN=./include/version.h
OUT=./genver.h
touch main.c
echo "char *genver=\" <<Generated at "`date`">> \";" > $OUT
