// tcl.com v1.0 (c) 2025 Pedro de Medeiros
#include "msxgl.h"
#include "dos.h"

// Data to send to tcl_bridge
struct {
    c8* output;         // offset + 0
    u16 output_size;    // offset + 2
    c8* input;          // offset + 4
    u16 input_size;     // offset + 6
    u16 input_max;      // offset + 8
    i8  status;         // offset + 10
} tcl_data;

#define MAX 1000
c8 input[MAX] = "tcl_bridge not running.$";

// Send command to Tcl engine
c8* tcl(void* data)
{
    data; // assumption: hl <- data
    __asm
        // write address
        ld c, #6
        out (c), l
        out (c), h
    __endasm;
    return input;
}

unsigned int strlen(c8* s)
{
    unsigned int i = 0;
    for (i = 0; s[i] != 0; ++i);
    return i;
}

void main(u8 argc, c8** argv)
{
    if (argc < 1) {
        DOS_StringOutput("tcl.com v1.0 (c) 2025 Pedro de Medeiros\r\n$");
        DOS_StringOutput("No arguments $$ provided.$");
        DOS_Exit0();
    }

    // concatenate all command line parameters
    for (u8 i = 0; i < argc; i++) {
        argv[i][-1] = ' ';
    }

    tcl_data.output      = argv[0];
    tcl_data.output_size = strlen(argv[0]);
    tcl_data.input       = input;
    tcl_data.input_max   = MAX;
    c8* s = tcl(&tcl_data); // here tcl_data fields are magically filled in...
    s[tcl_data.input_size] = '$';
    DOS_StringOutput(s);
    DOS_Exit0();
}

