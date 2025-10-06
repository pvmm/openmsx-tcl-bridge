// tcl.com v1.0 (c) 2025 Pedro de Medeiros
//
// tcl.com doesn't implement all details of tcl_bridge. Namely, it doesn't
// treat input as a binary data.

#include "msxgl.h"
#include "dos.h"
#include "string.h"

// Data to send to tcl_bridge
struct {
    c8* output;         // offset + 0
    u16 output_size;    // offset + 2
    c8* input;          // offset + 4
    u16 input_max;      // offset + 6
    u16 input_size;     // offset + 8
    i8  status;         // offset + 10
} tcl_data;

#define INPUT_MAX 100
c8 input[INPUT_MAX] = {0};

// Send command to Tcl engine
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

void main(u8 argc, c8** argv)
{
    if (argc < 1) {
        DOS_StringOutput("tcl.com v1.0 (c) 2025 Pedro de Medeiros\r\n$");
        DOS_StringOutput("No arguments provided.$");
        DOS_Exit0();
    }

    // concatenate all command line parameters
    for (u8 i = 0; i < argc; i++) {
        argv[i][-1] = ' ';
    }

    tcl_data.output      = argv[0];
    tcl_data.output_size = String_Length(argv[0]);
    tcl_data.input       = input;
    tcl_data.input_max   = INPUT_MAX;
    tcl_data.status      = 0x7F;
    tcl(&tcl_data); // here tcl_data fields are magically filled in...
    if (tcl_data.status == 0x7F) {
        DOS_StringOutput("tcl_bridge not running.$");
    } else if (tcl_data.input_size > tcl_data.input_max) {
        DOS_StringOutput("Buffer too small to receive full result.$");
    } else if (tcl_data.input_size == 0) {
        DOS_StringOutput("Empty result.$");
    } else {
        input[(tcl_data.input_size == INPUT_MAX ? 1 : 0)] = '$';
        DOS_StringOutput(input);
    }
    DOS_Exit0();
}

