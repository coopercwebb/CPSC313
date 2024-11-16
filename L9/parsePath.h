#ifndef PARSE_PATH_H
#define PARSE_PATH_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    /* It is up to you to define the contents of this struct. */
} path_parser_t;

/*
 * Return a new path parser for the given string representing (hopefully)
 * a path.
 */
path_parser_t *new_path_parser(char * str);

/*
 * Return the next component of the path, or NULL if no such component
 * exists.
 */
char *next_path_component(path_parser_t *path_parser);

/*
 * Dispose of a path parser by freeing all malloc'ed memory.
 */
void free_path_parser(path_parser_t *path_parser);

#endif
