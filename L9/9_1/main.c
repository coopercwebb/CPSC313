#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "hexdump.h"

/*
 * Test student hexdump.
 */
int main(int argc, char *argv[]) {
	char *outfile;

	if (argc != 2) {
		fprintf(stderr, "Usage: hextest infile\n");
		return 1;
	}

	// Allocate enough space to add ".txt" to file name
	outfile = malloc(strlen(argv[1]) + strlen(".txt") + 1);
	if (outfile == NULL) {
		fprintf(stderr, "Unable to malloc space for output file name.\n");
		return 1;
	}
	strcpy(outfile, argv[1]);
	strcpy(outfile+strlen(argv[1]), ".txt");

	// Call hexdump
	printf("Creating hexdump of file %s in file %s\n", argv[1], outfile);
	return hexdump(argv[1], outfile);
}
