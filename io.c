// io.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Modul io.c obsahujúci funkciu read_word

#include "io.h"
#include "error.h"

int read_word(char *s, int max, FILE *f)
{
    if (f == NULL)
    {
        warning_msg("io:Subor sa nepodarilo precitat\n");
    }

    bool limit = false;
    int c;
    int length = 0;

    while ((c = fgetc(f)) != EOF && isspace(c))
        ;

    if (c == EOF)
    {
        return EOF;
    }
    s[length++] = c;

    while ((c = fgetc(f)) != EOF && !isspace(c))
    {
        s[length] = c;
        length++;

        if (length == max - 1)
        {
            limit = true;
            break;
        }
    }
    s[length] = '\0';

    if (limit && !isspace(fgetc(f)))
    {
        while ((c = fgetc(f)) != EOF && !isspace(c))
            ;
        return 0;
    }

    return length;
}