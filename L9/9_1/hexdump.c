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
  // int fd_in;
  // int fd_out;
  // char buf[16];

  // // opens file in read-only mode
  // fd_in = open(infile, O_RDONLY);
  // if (fd_in == -1) {
  //     return 0;
  // }

  // fd_out = open(outfile, O_CREAT | O_WRONLY, 0644);
  // if (fd_out == -1) {
  //     close(fd_in);
  //     return 0;
  // }

  // int offset = 0;
  // ssize_t bytesToRead;

  // while ((bytesToRead = read(fd_in, buf, 16)) > 0) {
  //     fprintf(fd_out, "%08x", offset);
  //     }

  // }

  return 1;
}
