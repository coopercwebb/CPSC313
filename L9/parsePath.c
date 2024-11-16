#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "parsePath.h"

/**
 * Parse an input string according to examples in test.cpp
 * 1. The caller is not responsible for freeing the char array you return.
 * 2. The returned char array must be writable (write your own test to verify your implementation). 
 * 3. Do not forget to complete the struct definition in parsePath.h.
 */

/*
 * Return a new path parser for the given string representing (hopefully)
 * a path.
 */
path_parser_t *new_path_parser(char * str)
{
    (void) str;
    return NULL;
}

/*
 * Return the next component of the path, or NULL if no such component
 * exists.
 */
char *next_path_component(path_parser_t *path_parser)
{
    (void) path_parser;
    return NULL;
}

/*
 * Dispose of a path parser by freeing all malloc'ed memory.
 */
void free_path_parser(path_parser_t *path_parser)
{
    (void) path_parser;
}
