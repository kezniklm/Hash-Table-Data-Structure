// htab_find.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Vyhladá položku - vráti ukazatel v prípade úspechu, alebo NULL v prípade neúspechu

#include "htab_private.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
    size_t idx = htab_hash_function(key);
    idx %= t->arr_size;

    if (t->arr_ptr[idx] == NULL)
    {
        return NULL;
    }

    for (struct htab_item *temp = t->arr_ptr[idx]; temp != NULL; temp = temp->next)
    {
        if (strlen(temp->pair->key) == strlen(key) && !strncmp(temp->pair->key, key, strlen(temp->pair->key)))
        {
            return temp->pair;
        }
    }
    return NULL;
}