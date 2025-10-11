#include "common.h"

struct tcl_data tcl_data = {0};

void tcl(void* data)
{
    data; // assumption: hl <- data
    __asm
        // write address
        ld c, #6
        out (c), l
        out (c), h
    __endasm;
}

void print(c8* buffer, u16 length)
{
    for (int i = 0; i < length; ++i) {
        DOS_CharOutput(buffer[i]);
    }
}

void flat(u8 argc, c8** argv)
{
    // concatenate all command line parameters
    u8* last_pos = argv[argc - 1] + String_Length(argv[argc - 1]) - 1;
    for (u8* p = argv[0]; p < last_pos; ++p) {
        if (*p == '\0') *p = ' ';
    }
}

void print_result()
{
    if (tcl_data.status == 0x7F) {
        DOS_StringOutput("tcl_bridge not running.$");
        return;
    }
    if (tcl_data.status == 1) DOS_StringOutput("Error: $");
    print(tcl_data.res_addr, MIN(tcl_data.res_real_len, tcl_data.res_max_len));
    if (tcl_data.res_real_len > tcl_data.res_max_len) DOS_StringOutput("... <truncated>$");
}
