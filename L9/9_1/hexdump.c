#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "hexdump.h"

/**
 * Generate the hexdump of infile, and write result to outfile
 * 1. return 1 if success, and 0 otherwise
 * 2. outfile should not be created if infile does not exist
 */
int hexdump(const char *infile, const char *outfile) {

    // opens file in read-only mode
    int fd_in = open(infile, O_RDONLY);
    if (fd_in == -1) {
        return 0;
    }

    int fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd_out == -1) {
        close(fd_in);
        return 0;
    }

    int32_t offset = 0x0;
    ssize_t bytes_read;
    char buf[16];

    while ((bytes_read = read(fd_in, buf, 16)) > 0) {
        printf("%08x       ", offset);
        printf("%x", buf[0] & 0xFF);
        for (int i = 1; i < bytes_read; i++) {
            if (i == 8) {
                printf("    ");
            } else {
                printf(" ");
            }
            printf("%x", buf[i] & 0xFF);
        }
        printf("\n");
        offset += bytes_read;
    }

    printf("%08x\n", offset);

    close(fd_in);
    close(fd_out);

    return 1;
}
