// htab_clear.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Zruší všetky položky, tabuľka zostane prázdna

#include <stdlib.h>
#include "htab_private.h"

void htab_clear(htab_t *t)
{
    for (size_t i = 0; i < t->arr_size; i++)
    {
        for (struct htab_item *temp = t->arr_ptr[i]; temp != NULL; temp = temp->next)
        {
            if (temp->next == NULL)
            {
                free((char *)temp->pair->key);
                free(temp);
                break;
            }

            struct htab_item *temp2 = temp->next;
            while (temp2 != NULL)
            {
                free((char *)temp->pair->key);
                free(temp);
                temp = temp2;
                temp2 = temp2->next;
            }

            free((char *)temp->pair->key);
            free(temp);
        }
        t->arr_ptr[i] = NULL;
    }
    t->size = 0;
}