// tcl.com v1.0 (c) 2025 Pedro de Medeiros
//
// tcl.com implements tcl_bridge as a reference implementation.
//
// tcl.com doesn't implement all details of tcl_bridge. Namely, it doesn't
// treat command result as binary data.

#include "msxgl.h"
#include "dos.h"
#include "string.h"

// Data to send to tcl_bridge
struct {
    c8* cmd_addr;       // offset + 0
    u16 cmd_len;        // offset + 2
    c8* res_addr;       // offset + 4
    u16 res_max_len;    // offset + 6
    u16 res_real_len;   // offset + 8
    i8  status;         // offset + 10
    i8  res_modifier;   // offset + 11
} tcl_data;

#define RESPONSE_MAX 1000
c8 response[RESPONSE_MAX] = {0};

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

void print(c8* buffer, u16 length)
{
    for (int i = 0; i < length; ++i) {
        DOS_CharOutput(buffer[i]);
    }
}

void main(u8 argc, c8** argv)
{
    if (argc < 1) {
        DOS_StringOutput("tcl.com v1.0 (c) 2025 Pedro de Medeiros\r\n$");
        DOS_StringOutput("No arguments provided.$");
        DOS_Exit0();
    }

    // concatenate all command line parameters
    u8* last_pos = argv[argc - 1] + String_Length(argv[argc - 1]) - 1;
    for (u8* p = argv[0]; p < last_pos; ++p) {
        if (*p == '\0') *p = ' ';
    }

    // populate tcl_data and send to tcl_bridge
    tcl_data.cmd_addr     = argv[0];
    tcl_data.cmd_len      = String_Length(argv[0]);
    tcl_data.res_addr     = response;
    tcl_data.res_max_len  = RESPONSE_MAX;
#ifdef MODIFIER
    tcl_data.res_modifier = MODIFIER;
#else
    tcl_data.res_modifier = 0;
#endif
    tcl_data.status       = 0x7F; // if this changes tcl_bridge is alive

    tcl(&tcl_data); // here tcl_data fields are magically filled in...

    if (tcl_data.status == 0x7F) {
        DOS_StringOutput("tcl_bridge not running.$");
        DOS_Exit0();
    }
    if (tcl_data.status == 1) DOS_StringOutput("Error: $");
    if (tcl_data.res_real_len > tcl_data.res_max_len) {
        print(response, tcl_data.res_max_len);
        DOS_StringOutput("... truncated!\r\nBuffer too small to receive full result.$");
    } else if (tcl_data.res_real_len == 0) {
        DOS_StringOutput("Empty result.$");
    } else {
        print(response, tcl_data.res_real_len);
    }
    DOS_Exit0();
}

