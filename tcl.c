// tcl.com v1.0 (c) 2025 Pedro de Medeiros
#include "msxgl.h"
#include "dos.h"

// Send command to Tcl engine
bool tcl(char* s)
{
    s; // assumption: hl <- s
    __asm
        // write address
        ld c, #6
        out (c), l
        out (c), h
        // read response
        ld h, #0
        ld c, #7
        in l, (c)
    __endasm;
    return s == 0;
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

    DOS_StringOutput(tcl(argv[0]) ? "OK$" : "ERROR$");
    DOS_Exit0();
}

