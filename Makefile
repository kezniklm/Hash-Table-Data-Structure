#Makefile
#Riesenie IJC-DU2 - priklad A,B 
#Datum odovzdania: 22.3.2022
#Autor: Matej Keznikl
#Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
#Prelozene: GCC 7.5.0
#Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
#Popis: Makefile pre IJC projekt_2

CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra

LIBRARY_SOURCES=$(wildcard htab*.c)
LIBRARY_OBJECTS=$(patsubst %.c,%.o,$(LIBRARY_SOURCES))
LIBRARY_HEADERS=htab.h htab_private.h

all: tail wordcount wordcount-dynamic

tail: tail.o error.o
	$(CC) $(CFLAGS) tail.o error.o -o tail

wordcount: wordcount.o error.o io.o libhtab.a 
	$(CC) $(CFLAGS) wordcount.o error.o io.o -o $@ -static -L. -lhtab

wordcount-dynamic: wordcount.o error.o io.o libhtab.so
	$(CC) $(CFLAGS) wordcount.o error.o io.o -o $@ -L. -lhtab

error.o: error.h error.c 
	$(CC) $(CFLAGS) -c error.c -o error.o

tail.o: tail.h tail.c 
	$(CC) $(CFLAGS) -c tail.c -o tail.o

wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $<

htab_%.o: CFLAGS+=-fPIC
libhtab.so: CFLAGS+=-fPIC

htab_%.o: htab_%.c LIB_HEADERS
	$(CC) $(CFLAGS) -c $<

libhtab.a: $(LIBRARY_OBJECTS) $(LIBRARY_HEADERS)
	ar rcs $@ $^

libhtab.so: $(LIBRARY_OBJECTS) $(LIBRARY_HEADERS)
	$(CC) $(CFLAGS) -shared $^ -o $@

zip:
	zip xkezni01.zip *.c *.cc *.h Makefile

run:
	export LD_LIBRARY_PATH="." && ./wordcount-dynamic

.PHONY: clean
clean:
	rm -f *.o
	rm -f tail
	rm -f wordcount
	rm -f wordcount-dynamic
#   rm -f *.so
#   rm -f *.a