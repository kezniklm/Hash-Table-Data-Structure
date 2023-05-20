// io.h
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavičkový súbor pre io.c

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// funkcia ktorá počíta dĺžku slova
int read_word(char *s, int max, FILE *f);

#endif
