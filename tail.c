// tail.c
// Riesenie IJC-DU2 - priklad A,B
// Datum odovzdania: 19.4.2022
// Autor: Matej Keznikl
// Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
// Prelozene: GCC 7.5.0
// Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
// Popis: Program tail, ktorý funguje ako POSIX tail

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tail.h"
#include "error.h"

#define LINE_LIMIT 4095
#define DEFAULT_LINE_N 10
#define NO_ARGUMENTS 1

// funkcia na overenie platnosti argumentov
long arguments(int argc, char *argv[], char **name_of_file)
{
	long limit = 0;
	for (int i = 1; i < argc; i++)
	{
		if (!limit)
		{
			if (!(strcmp(argv[i], "-n")))
			{
				if (argv[i + 1] != NULL)
				{
					char *ptr;
					limit = strtol(argv[i + 1], &ptr, 10);
					if (*ptr != '\0')
					{
						error_exit("tail: V prípade zadaného argumentu -n je potrebné zadat ďalší argument kladné číslo");
					}
					if (limit < 0)
					{
						error_exit("tail: V prípade zadaného argumentu -n je potrebné zadat ďalší argument kladné číslo");
					}
				}
				if (!(strcmp("-n", argv[argc - 1])))
				{
					error_exit("tail: V prípade zadaného argumentu -n je potrebné zadat ďalší argument kladné číslo");
				}
			}
		}
		if (argv[i] != NULL)
		{
			char *name;
			long number = 0;
			number = strtol(argv[i], &name, 10);
			if (number == 0 && strcmp(name, "-n"))
			{
				FILE *fp;
				fp = fopen(argv[i], "r");
				if (fp)
				{
					*name_of_file = argv[i];
					fclose(fp);
				}
				else
					error_exit("tail: Subor %s nebolo mozne otvorit\n", argv[i]);
			}
		}
	}
	return limit;
}

// funkcia tail - vypíše posledných n riadkov podla zadaného parametra n, v prípade nezadaného parametra n funkcia vypíše posledných 10 riadkov
void tail(long number_of_lines, char *filename)
{
	FILE *file_pointer;
	if (filename != 0)
	{
		file_pointer = fopen(filename, "r");

		// kontrola, ci sa funkcii fopen podarilo subor otvorit
		if (file_pointer == NULL)
		{
			error_exit("tail: Subor %s nebolo mozne otvorit\n", filename);
		}
	}
	else
		file_pointer = stdin; // v prípade, že sa nepodarilo súbor otvoriť, čítame zo štandardného vstupu - stdin

	// Alokovanie pamäte podľa zadaného parametra n - z dôvodu uloženia práve n riadkov
	char **buffer = calloc(number_of_lines, sizeof(char *));

	// v prípade, že alokácia nebola úspešná, voláme funkciu error_exit
	if (buffer == NULL)
	{
		error_exit("tail: Alokácia bufferu neprebehla úspešne");
	}

	for (long i = 0; i < number_of_lines; i++)
	{
		// Alokovanie pamäte podľa zadaného implementačného limitu - dĺžky riadka
		buffer[i] = calloc(LINE_LIMIT + 2, sizeof(char));

		// v prípade, že alokácia nebola úspešná, voláme funkciu error_exit
		if (buffer[i] == NULL)
		{
			error_exit("tail: Alokácia bufferu neprebehla úspešne");
		}
	}

	int first_warning = 0;
	long i = 0;
	// načítanie textu zo súboru
	while (fgets(buffer[i % number_of_lines], LINE_LIMIT + 1, file_pointer) != NULL)
	{
		// overenie či daný riadok nepresiahol limit
		if ((strlen(buffer[i % number_of_lines]) == LINE_LIMIT) && (buffer[i % number_of_lines][LINE_LIMIT - 1] != '\n'))
		{
			buffer[i % number_of_lines][LINE_LIMIT] = '\n';
			buffer[i % number_of_lines][LINE_LIMIT + 1] = '\0';
			while (getc(file_pointer) != '\n')
				;

			// v prípade, že riadok prvý krát presiahol limit, vypíše sa chybové hlásenie a pokračuje sa zo skrátenými riadkami
			if (!first_warning)
			{
				warning_msg("tail: Bol prekročený limit dĺžky riadka\n");
				first_warning = 1;
			}
		}
		i++;
	}

	// V prípade, že počet riadkov je menší ako N, tak sa vypíše iba daný počet riadkov
	if (i < number_of_lines)
	{
		for (long j = 0; j < number_of_lines; j++)
		{
			printf("%s", buffer[j]);
		}
	}

	// výpis posledných N riadkov
	if (i >= number_of_lines)
	{
		for (long j = i - number_of_lines; j < i; j++)
		{
			printf("%s", buffer[j % number_of_lines]);
		}
	}

	// uvoľnenie prvkov bufferu z pamäti
	for (long i = 0; i < number_of_lines; i++)
	{
		free(buffer[i]);
	}

	// uvolnenie bufferu z pamäti
	free(buffer);

	fclose(file_pointer);
}

int main(int argc, char *argv[])
{
	long n = 0;
	char *name_of_file;

	// v prípade, že argc == 1, tak program nedostal žiadne argumenty
	if (argc != NO_ARGUMENTS)
	{
		n = arguments(argc, argv, &name_of_file);
	}

	// v prípade, že nebol zadaný parameter -n program pokračuje s -n = 10
	if (!n)
	{
		n = DEFAULT_LINE_N;
	}

	tail(n, name_of_file);

	return 0;
}