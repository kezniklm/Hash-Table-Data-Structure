// htab_free.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Deštruktor - zruší tabulku - volá htab_clear

#include <stdlib.h>
#include "htab_private.h"

void htab_free(htab_t *t)
{
    htab_clear(t);
    free(t);
}