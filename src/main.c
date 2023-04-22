/*
 * GRAUS - A Generator for Random Alphanumeric Uppercase Strings.
 *
 * (C) Copyright 2023 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See LICENSE file for details or copy at https://opensource.org/licenses/MIT
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cargs.h"

#define VERSION ("0.1.0-alpha.1")

#define LEN_MIN     (1U)
#define LEN_MAX     (100U)
#define LEN_DEFAULT (10U)

#define NUM_MIN     (1U)
#define NUM_MAX     (100U)
#define NUM_DEFAULT (1U)

static const struct cag_option options[] =
{
    {
        .identifier = 'l',
        .access_letters = "l",
        .access_name = "length",
        .value_name = "LENGTH",
        .description = "Length of string(s) (1..100) (default: 10)"
    },
    {
        .identifier = 'n',
        .access_letters = "n",
        .access_name = "number",
        .value_name = "NUMBER",
        .description = "Number of strings to be generated (1..100) (default: 1)"
    },
    {
        .identifier = 'h',
        .access_letters = "h",
        .access_name = "help",
        .value_name = NULL,
        .description = "Shows the command help"
    },
    {
        .identifier = 'v',
        .access_letters = "v",
        .access_name = "version",
        .value_name = NULL,
        .description = "Show the program version"
    }
};

const char characters[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

int
arg_to_uint(const char* arg_raw, unsigned int* arg, unsigned int min, unsigned int max);

int
main(int argc, char *argv[])
{
    char identifier;
    uintptr_t seed = (uintptr_t)&identifier;
    cag_option_context context;
    unsigned int length = LEN_DEFAULT;
    unsigned int number = NUM_DEFAULT;
    const char* arg_raw;

    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
    while (cag_option_fetch(&context))
    {
        identifier = cag_option_get(&context);
        switch (identifier)
        {
            case 'l':
                arg_raw = cag_option_get_value(&context);
                if (!arg_to_uint(arg_raw, &length, LEN_MIN, LEN_MAX))
                {
                    printf("Length must be in range %u to %u!\n", LEN_MIN, LEN_MAX);
                    return EXIT_FAILURE;
                }
                break;
            case 'n':
                arg_raw = cag_option_get_value(&context);
                if (!arg_to_uint(arg_raw, &number, NUM_MIN, NUM_MAX))
                {
                    printf("Number of strings must be in range %u to %u!\n", NUM_MIN, NUM_MAX);
                    return EXIT_FAILURE;
                }
                break;
            case 'v':
                printf("GRAUS %s\n", VERSION);
                return EXIT_SUCCESS;
            case 'h':
                printf("Usage: graus [OPTION]...\n");
                printf("GRAUS - A Generator for Random Alphanumeric Uppercase Strings.\n\n");
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                printf("\nThis program generates a number of pseudo random alphanumeric uppercase strings.\n");
                return EXIT_SUCCESS;
            default:
                printf("Usage: graus [OPTION]...\n");
                return EXIT_FAILURE;
        }
    }

    for (unsigned int n = 0U; n < number; n++)
    {
        srand(time(NULL) + (unsigned int)seed + n);
        for (unsigned int l = 0; l < length; l++)
        {
            int random_variable = rand();
            putchar(characters[(unsigned int)random_variable % (sizeof(characters)/sizeof(char))]);
        }
        putchar('\n');
    }

    return EXIT_SUCCESS;
}

int
arg_to_uint(const char* arg_raw, unsigned int* arg, unsigned int min, unsigned int max)
{
    assert(arg_raw != NULL);
    assert(arg != NULL);

    char* p;
    long tmp;

    tmp = strtol(arg_raw, &p, 10);

    if ((*p != '\0') || (errno != 0))
    {
        return 0;
    }

    if (tmp < 0)
    {
        return 0;
    }

    if (((unsigned int)tmp < min) || (((unsigned int)tmp > max)))
    {
        return 0;
    }

    *arg = (unsigned int) tmp;

    return 1;
}
