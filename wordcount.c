// wordcount.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul obsahujuci funkciu wordcount pre počítanie slov

#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "htab.h"
#include "error.h"

#define MAX_WORD_LEN 127
#define HASHTAB_SIZE 27000

void print_record(htab_pair_t *data)
{
    printf("%s\t%d\n", data->key, data->value);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc == 2)
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            error_exit("wordcount: Subor sa nepodarilo otvorit");
        }
    }
    else
        fp = stdin;

    htab_t *p = htab_init(HASHTAB_SIZE);
    if (p == NULL)
    {
        fclose(fp);
        error_exit("wordcount: Inicializácia hashovacej tabulky zlyhala");
    }

    char *buffer = calloc(MAX_WORD_LEN,sizeof(char));
    if(buffer == NULL)
    {
        error_exit("wordcount: Alokácia pamäte zlyhala");
    }
    int limit = 0;
    int length;

    while ((length = read_word(buffer, MAX_WORD_LEN, fp)) != EOF)
    {
        if (length == 0 && limit == 0)
        {
            limit = 1;
            warning_msg("V texte su prilis dlhe slova - program ich skráti\n");
        }

        if (htab_lookup_add(p, buffer) == NULL)
        {
            htab_free(p);
            free(buffer);
            fclose(fp);
            error_exit("wordcount: Prvok tabulky nebol správne alokovaný, program sa ukonci");
        }
    }

    htab_for_each(p, print_record);

    free(buffer);
    fclose(fp);
    return 0;
}
