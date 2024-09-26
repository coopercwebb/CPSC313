#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Here are the enumerated types for each instruction. */
typedef enum _inst_t {
        I_NOP,
        I_HALT,
        I_RRMOVQ,
        I_IRMOVQ,
        I_RMMOVQ,
        I_MRMOVQ,
        I_PUSHQ,
        I_POPQ,
        I_CALL,
        I_RET,
        I_J,
        I_JEQ,
        I_JNE,
        I_JL,
        I_JLE,
        I_JG,
        I_JGE,
        I_ADDQ,
        I_SUBQ,
        I_MULQ,
        I_MODQ,
        I_DIVQ,
        I_ANDQ,
        I_XORQ,
        I_CMOVEQ,
        I_CMOVNE,
        I_CMOVL,
        I_CMOVLE,
        I_CMOVG,
        I_CMOVGE,
        I_INVALID
} inst_t;

/* This structure represents a mapping from a string name to an enum. */
struct cmd_map_t {
        char *cmd_str;
        inst_t cmd;
};

/* In main.c, you will find the actual definition of this structure. */
extern struct cmd_map_t cmd_map [30];

/* Here is the prototype for the function that you will write. */
inst_t inst_to_enum(const char *str);
