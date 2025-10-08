// tcl.com v1.0 (c) 2025 Pedro de Medeiros
//
// tcl.com implements tcl_bridge as a reference implementation.
//
// tcl.com doesn't implement all details of tcl_bridge. Namely, it doesn't
// treat command result as binary data.

#include "msxgl.h"
#include "dos.h"
#include "string.h"
#include "memory.h"
#include "math.h"

// Data to send to tcl_bridge
struct {
    c8* cmd_addr;       // offset + 0
    u16 cmd_len;        // offset + 2
    c8* res_addr;       // offset + 4
    u16 res_max_len;    // offset + 6
    u16 res_real_len;   // offset + 8
    i8  status;         // offset + 10
} tcl_data;

#define RESPONSE_MAX 1000
c8 response[RESPONSE_MAX] = {0};

#ifdef FORCE_TEXT_MODE

#define CMD_MAX 289
c8 prefixed_cmd[CMD_MAX] = "string map {\\n \\r\\n} [\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

#endif

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
    int arg_len = String_Length(argv[0]);
#ifdef FORCE_TEXT_MODE
    int prefixed_len = String_Length(prefixed_cmd);
    Mem_Copy(argv[0], prefixed_cmd + prefixed_len, arg_len);
    prefixed_cmd[prefixed_len + arg_len] = ']';
    tcl_data.cmd_addr     = prefixed_cmd;
    tcl_data.cmd_len      = prefixed_len + arg_len + 1;
#else
    tcl_data.cmd_addr     = argv[0];
    tcl_data.cmd_len      = String_Length(argv[0]);
#endif
    tcl_data.res_addr     = response;
    tcl_data.res_max_len  = RESPONSE_MAX;
    tcl_data.status       = 0x7F; // if this changes tcl_bridge is alive

    tcl(&tcl_data); // here tcl_data fields are magically filled in...

    if (tcl_data.status == 0x7F) {
        DOS_StringOutput("tcl_bridge not running.$");
        DOS_Exit0();
    }
    if (tcl_data.status == 1) DOS_StringOutput("Error: $");
    print(response, MIN(tcl_data.res_real_len, tcl_data.res_max_len));
    if (tcl_data.res_real_len > tcl_data.res_max_len) DOS_StringOutput("... <truncated>$");

#ifdef DOS2
    DOS_Exit(tcl_data.status);
#else
    DOS_Exit0();
#endif
}

