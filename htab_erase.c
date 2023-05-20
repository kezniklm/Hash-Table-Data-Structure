// htab_erase.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Zruší záznam s daným klúčom - vracia true v prípade úspechu

#include <stdlib.h>
#include "htab_private.h"

bool htab_erase(htab_t *t, htab_key_t key)
{
    size_t idx = htab_hash_function(key);
    idx %= t->arr_size;

    if (htab_find(t, key) == NULL)
    {
        return false;
    }

    struct htab_item *temp = t->arr_ptr[idx];
    if (strlen(temp->pair->key) == strlen(key) && !strncmp(temp->pair->key, key, strlen(temp->pair->key)))
    {
        if (temp->next == NULL)
        {
            free((char *)temp->pair->key);
            free(temp);
            t->arr_ptr[idx] = NULL;
        }
        else
        {
            struct htab_item *temp2 = temp->next;
            free((char *)temp->pair->key);
            free(temp);
            t->arr_ptr[idx] = temp2;
        }

        t->size--;
        return true;
    }

    for (temp = t->arr_ptr[idx]; temp->next != NULL; temp = temp->next)
    {
        if (strlen(temp->next->pair->key) == strlen(key) &&
            !strncmp(temp->next->pair->key, key, strlen(temp->next->pair->key)))
        {
            struct htab_item *temp2 = temp->next->next;
            free((char *)temp->next->pair->key);
            free(temp->next);
            temp->next = temp2;
        }
    }

    t->size--;
    if (t->arr_size > 1)
    {
        if (t->size / t->arr_size < AVG_LEN_MIN)
        {
            htab_resize(t, t->arr_size / 2);
        }
    }
    return true;
}