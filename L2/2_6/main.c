#include "insts.h"
#include <stdio.h>

struct cmd_map_t cmd_map[30] = {
    {"nop", I_NOP},
    {"halt", I_HALT},
    {"rrmovq", I_RRMOVQ},
    {"irmovq", I_IRMOVQ},
    {"rmmovq", I_RMMOVQ},
    {"mrmovq", I_MRMOVQ},
    {"pushq", I_PUSHQ},
    {"popq", I_POPQ},
    {"call", I_CALL},
    {"ret", I_RET},
    {"jmp", I_J},
    {"je", I_JEQ},
    {"jne", I_JNE},
    {"jl", I_JL},
    {"jle", I_JLE},
    {"jg", I_JG},
    {"jge", I_JGE},
    {"addq", I_ADDQ},
    {"subq", I_SUBQ},
    {"mulq", I_MULQ},
    {"modq", I_MODQ},
    {"divq", I_DIVQ},
    {"andq", I_ANDQ},
    {"xorq", I_XORQ},
    {"cmove", I_CMOVEQ},
    {"cmovne", I_CMOVNE},
    {"cmovl", I_CMOVL},
    {"cmovle", I_CMOVLE},
    {"cmovg", I_CMOVG},
    {"cmovge", I_CMOVGE}};

/*
 * This is an interactive test program that will let you
 * type in commands and get a value back (it's your job
 * to either enhance this program to be more useful or to
 * manually confirm that you are returning the right value).
 */
int main(int argc, char *argv[]) {
    char cmd[129] = "";
    inst_t token;

    while (1) {
        printf("Command : ");
        if (scanf("%128s", cmd) <= 0)
            return 0;
        token = inst_to_enum(cmd);
        printf("%d\n", (int)token);
    }
}
