#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#include "dirLookup.h"

CS313ino_t dirLookup(const char *filename, const char *component) {

    // https://man7.org/linux/man-pages/man3/fread.3.html

    // Remove these two lines once you are using the parameters.
    // (void)filename;
    (void)component;

    FILE *file_in = fopen(filename, "rb");
    if (file_in == NULL) {
        return 0;
    }

    unsigned char buf[sizeof(dir_entry_t)];
    size_t bytes_read;
    size_t bytes_read_cont;
    dir_entry_t *decode;

    // Important Note: The normal (C) rules for stucture size and alignment don't apply to directory entries.
    // No matter the sizes of the fields of a directory entry, the size of each directory entry is rounded
    // up to a multiple of 4 bytes.

    while ((bytes_read = fread(buf, sizeof(*buf), sizeof(dir_entry_t) - 256, file_in)) > 0) {
        decode = (dir_entry_t *)buf;

        unsigned int name_len = decode->de_namelen;

        unsigned int total_bytes = sizeof(dir_entry_t) - 256 + decode->de_namelen;
        unsigned int remainder = (total_bytes % 4);

        if (remainder > 0) {
            // Need to round up to nearest multiple of 4
            name_len += (4 - remainder);
        }

        // + 1 on namelen to account for \0
        if ((bytes_read = fread(buf + (sizeof(dir_entry_t) - 256), sizeof(*buf), name_len, file_in) > 0)) {
            decode = (dir_entry_t *)buf;
        }
        printf("test\n");
    }

    fclose(file_in);

    return BAD_DIR_ENTRY_INODE_NUMBER;
}
