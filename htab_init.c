// htab_init.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Konštruktor hash tabuľky - vytvára a inicializuje tabulku

#include <stdlib.h>
#include "htab_private.h"

htab_t *htab_init(size_t n)
{
    if (n <= 0)
    {
        return NULL;
    }

    htab_t *hash_table = malloc(sizeof(htab_t));

    if (hash_table == NULL)
    {
        return NULL;
    }

    hash_table->size = 0;
    hash_table->arr_size = n;
    hash_table->arr_ptr = calloc(n, sizeof(struct htab_item *));

    if (hash_table->arr_ptr == NULL)
    {
        return NULL;
    }

    return hash_table;
}