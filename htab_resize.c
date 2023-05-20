// htab_resize.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul obsahujuci funkciu htab_resize

#include <stdlib.h>
#include "htab.h"
#include "htab_private.h"

void htab_resize(htab_t *t, size_t newn)
{
    if (t == NULL || newn <= 0)
    {
        return;
    }

    htab_t *new_htab = htab_init(newn);
    if (new_htab == NULL)
    {
        return;
    }

    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *ptr = t->arr_ptr[i];

        while (ptr != NULL)
        {
            size_t new_index = htab_hash_function(ptr->pair->key) % newn;
            struct htab_item *new_item = calloc(1, sizeof(struct htab_item));

            if (new_item == NULL)
            {
                for (size_t i = 0; i < t->arr_size; i++)
                {
                    if (t->arr_ptr[i] == NULL)
                    {
                        continue;
                    }

                    struct htab_item *ptr = t->arr_ptr[i];
                    while (ptr != NULL)
                    {
                        struct htab_item *next = ptr->next;
                        free(ptr);
                        ptr = next;
                    }
                }

                free(t->arr_ptr);
                free(t);
            }

            new_item->pair = ptr->pair;
            new_item->next = NULL;

            if (new_htab->arr_ptr[new_index] == NULL)
            {
                new_htab->arr_ptr[new_index] = new_item;
            }
            else
            {
                struct htab_item *n = new_htab->arr_ptr[new_index];

                while (n->next != NULL)
                {
                    n = n->next;
                }

                n->next = new_item;
            }

            ptr = ptr->next;
        }
    }

    new_htab->size = t->size;
    htab_t *tmp = t;
    t = new_htab;
    for (size_t i = 0; i < tmp->arr_size; i++)
    {
        if (tmp->arr_ptr[i] == NULL)
        {
            continue;
        }

        struct htab_item *ptr = tmp->arr_ptr[i];
        while (ptr != NULL)
        {
            struct htab_item *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }

    free(tmp->arr_ptr);
    free(tmp);
}
