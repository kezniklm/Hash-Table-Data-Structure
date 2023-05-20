// htab_size.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Vráti počet prvkov tabulky (.size)

#include "htab_private.h"

size_t htab_size(const htab_t *t)
{
    return t->size;
}