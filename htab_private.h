// htab_private.h
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Hlavičkový súbor pre htab

#ifndef __HTABLE_PRIVATE_H__
#define __HTABLE_PRIVATE_H__

#include "htab.h"

struct htab
{
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

struct htab_item
{
    htab_pair_t *pair;
    struct htab_item *next;
};

#endif