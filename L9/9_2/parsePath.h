#ifndef PARSE_PATH_H
#define PARSE_PATH_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    /* TODO: It is up to you to define the contents of this struct. */
    char **path_buf;
    int len;
    int cnt;
} path_parser_t;

/*
 * Return a new path parser for the given string representing (hopefully)
 * a path.
 */
path_parser_t *new_path_parser(char *str);

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
