// htab_lookup_add.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Vyhladá záznam odpovedajúci záznamu key, pokial ho nájde, vráti ukazatel na záznam

#include <stdlib.h>
#include "htab_private.h"

struct htab_item *create_item(htab_key_t k)
{
    htab_pair_t *pair = calloc(1, sizeof(htab_pair_t));
    struct htab_item *item = calloc(1, sizeof(struct htab_item));
    char *key = calloc(strlen(k) + 1, sizeof(char));

    if (k == NULL || pair == NULL || item == NULL)
    {
        return NULL;
    }

    strcpy(key, k);
    pair->key = key;
    pair->value = 1;
    item->pair = pair;
    item->next = NULL;

    return item;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    if (t == NULL)
    {
        return NULL;
    }

    size_t idx = htab_hash_function(key) % t->arr_size;

    if (t->arr_ptr[idx] == NULL)
    {
        t->arr_ptr[idx] = create_item(key);
        if (t->arr_ptr[idx] == NULL)
        {
            return NULL;
        }

        t->size += 1;
        return t->arr_ptr[idx]->pair;
    }

    struct htab_item *item_ptr = t->arr_ptr[idx];

    while (item_ptr != NULL)
    {
        if (strcmp(key, item_ptr->pair->key) == 0)
        {
            item_ptr->pair->value++;
            return item_ptr->pair;
        }

        item_ptr = item_ptr->next;
    }

    item_ptr = create_item(key);

    if (item_ptr == NULL)
    {
        return NULL;
    }

    t->size += 1;
    return item_ptr->pair;
}