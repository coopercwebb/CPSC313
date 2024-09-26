#include "insts.h"
#include <string.h>

// Your function must be fewer than 20 lines of code (i.e., you cannot
// brute force the implementation). Our solution is 9 lines including
// everything below. (It can be written even more compactly, but you need
// not worry about doing so.)

// If str is a valid instruction (as defined in insts.h), return
// the corresponding enum. If str is not a valid instruction,
// return I_INVALID.
inst_t inst_to_enum(const char *str) {
    if (strlen(str) < 2 || strlen(str) > 6) {
        return I_INVALID;
    }

    for (int i = 0; i < sizeof(cmd_map) / sizeof(struct cmd_map_t); i++) {
        if (!strcmp(str, cmd_map[i].cmd_str)) {
            return cmd_map[i].cmd;
        }
    }

    return I_INVALID;
}