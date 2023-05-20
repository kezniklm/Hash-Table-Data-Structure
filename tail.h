// tail.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavičkový súbor pre tail.c

#ifndef TAIL_H
#define TAIL_H

// funkcia tail - vypíše posledných n riadkov podla zadaného parametra n, v prípade nezadaného parametra n funkcia vypíše posledných 10 riadkov
void tail(long number_of_lines, char *filename);

// funkcia na overenie platnosti argumentov
long arguments(int argc, char *argv[], char **name_of_file);

#endif