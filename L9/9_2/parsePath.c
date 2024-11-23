#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
path_parser_t *new_path_parser(char *str) {
    if (str == NULL) {
        return NULL;
    }
    if (str[0] == '\0') {
        return NULL;
    }
    char *str_cpy = strdup(str);

    path_parser_t *parser = (path_parser_t *)malloc(sizeof(path_parser_t));

    // Allocate 100 char ptrs
    parser->path_buf = malloc(1000 * sizeof(char *));
    parser->len = 0;
    parser->cnt = 0;

    if (str_cpy[0] == '/') {
        parser->path_buf[0] = strndup("/", 1);
        parser->len++;
    }

    char *token = strtok(str_cpy, "/");

    while (token != NULL) {
        parser->path_buf[parser->len] = strndup(token, strlen(token));
        printf("create: %s\n", token); // DEBUG LINE
        parser->len++;
        token = strtok(NULL, "/");
    }

    free(str_cpy);
    return parser;
}

/*
 * Return the next component of the path, or NULL if no such component
 * exists.
 */
char *next_path_component(path_parser_t *path_parser) {
    if (path_parser->cnt < path_parser->len) {
        path_parser->cnt++;
        printf("next path: %s\n", path_parser->path_buf[path_parser->cnt - 1]); // DEBUG LINE
        return path_parser->path_buf[path_parser->cnt - 1];
    }
    return NULL;
}

/*
 * Dispose of a path parser by freeing all malloc'ed memory.
 */
void free_path_parser(path_parser_t *path_parser) {
    if (path_parser == NULL) {
        return;
    }
    for (int i = 0; i < path_parser->len; i++) {
        free(path_parser->path_buf[i]);
    }
    free(path_parser->path_buf);
    free(path_parser);
}
