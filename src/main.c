/*
 * GRAUS - A Generator for Random Alphanumeric Uppercase Strings.
 *
 * (C) Copyright 2023 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See LICENSE file for details or copy at https://opensource.org/licenses/MIT
 */

#include "cargs.h"

#include <assert.h>
#include <errno.h>
#include <limits.h> /* INT_MAX */
#include <stdint.h> /* uintptr_t */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM "graus"
#define VERSION "0.1.0-alpha.2"

#define XSTR(s) STR(s)
#define STR(s) #s

#define LEN_MIN     1
#define LEN_MAX     100
#define LEN_DEFAULT 10

#define NUM_MIN     1
#define NUM_MAX     100
#define NUM_DEFAULT 1

static const struct cag_option options[] =
{
    {
        .identifier = 'l',
        .access_letters = "l",
        .access_name = "length",
        .value_name = "LENGTH",
        .description =  "Length of string(s) (" XSTR(NUM_MIN) ".." XSTR(NUM_MAX)
                        ") (default: " XSTR(NUM_DEFAULT) ")"
    },
    {
        .identifier = 'n',
        .access_letters = "n",
        .access_name = "number",
        .value_name = "NUMBER",
        .description = "Number of strings to be generated (" XSTR(LEN_MIN) ".."
                        XSTR(LEN_MAX) ") (default: " XSTR(LEN_DEFAULT) ")"
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


static int
arg_to_int( const char* arg_raw,
            int* arg,
            int min,
            int max)
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

    if ((tmp < 0) || (tmp > INT_MAX))
    {
        return 0;
    }

    if (((int)tmp < min) || (((int)tmp > max)))
    {
        return 0;
    }

    *arg = (int) tmp;

    return 1;
}

int
main(int argc, char** argv)
{
    char identifier;
    uintptr_t seed = (uintptr_t)&identifier;
    cag_option_context context;
    int length = LEN_DEFAULT;
    int number = NUM_DEFAULT;
    const char* arg_raw;

    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
    while (cag_option_fetch(&context))
    {
        identifier = cag_option_get(&context);
        switch (identifier)
        {
            case 'l':
                arg_raw = cag_option_get_value(&context);
                if (!arg_to_int(arg_raw, &length, LEN_MIN, LEN_MAX))
                {
                    fputs(
                        PROGRAM ": not a valid length\n"
                        "Try: '" PROGRAM " --help'\n", stderr);
                    exit(EXIT_SUCCESS);
                }
                break;
            case 'n':
                arg_raw = cag_option_get_value(&context);
                if (!arg_to_int(arg_raw, &number, NUM_MIN, NUM_MAX))
                {
                    fputs(
                        PROGRAM ": not a valid number of strings\n"
                        "Try: '" PROGRAM " --help'\n", stderr);
                    exit(EXIT_SUCCESS);
                }
                break;
            case 'v':
                fputs(PROGRAM " version " VERSION "\n", stdout);
                exit(EXIT_SUCCESS);
            case 'h':
                fputs("Usage: " PROGRAM " [options]\n", stdout);
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                exit(EXIT_SUCCESS);
            default:
                fputs(
                    PROGRAM ": invalid option\n"
                    "Try: '" PROGRAM " --help'\n", stderr);
                exit(EXIT_FAILURE);
        }
    }

    for (int n = 0; n < number; n++)
    {
        srand(time(NULL) + (unsigned int)seed + (unsigned int)n);
        for (int l = 0; l < length; l++)
        {
            int random_variable = rand();
            putchar(characters[ (unsigned int)random_variable %
                                (sizeof(characters)/sizeof(char)) ]);
        }
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
