// htab_for_each.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Prejde všetky záznamy, na všetky zavolá funkciu

#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{

    for (size_t i = 0; i < t->arr_size; i++)
    {
        struct htab_item *ptr = t->arr_ptr[i];
        while (ptr != NULL)
        {
            (*f)(ptr->pair);
            ptr = ptr->next;
        }
    }
}
