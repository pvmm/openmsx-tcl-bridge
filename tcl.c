// tcl.com v1.0 (c) 2025 Pedro de Medeiros
#include "msxgl.h"
#include "dos.h"

// Data to send to tcl_bridge
struct {
    c8* output;
    c8* input;
    u16 size;
} tcl_data;

#define SIZE 1000
c8 input[SIZE];

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
    return &input;
}

void main(u8 argc, c8** argv)
{
    if (argc < 1) {
        DOS_StringOutput("tcl.com v1.0 (c) 2025 Pedro de Medeiros\r\n$");
        DOS_StringOutput("No arguments provided.$");
        DOS_Exit0();
    }

    // Concatenate all command line parameters
    for (u8 i = 0; i < argc; i++) {
        argv[i][-1] = ' ';
    }

    tcl_data.output = argv[0];
    tcl_data.input  = input;
    tcl_data.size   = SIZE;
    DOS_StringOutput(tcl(&tcl_data));
    DOS_Exit0();
}

