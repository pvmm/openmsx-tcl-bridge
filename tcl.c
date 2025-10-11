// tcl.com v1.0 (c) 2025 Pedro de Medeiros
//
// tcl.com implements tcl_bridge as a reference implementation.
// tcl.com treats result from Tcl as text.

#include "common.h"
#include "tcl_cmd.h"

void main(u8 argc, c8** argv)
{
    if (argc < 1) {
        DOS_StringOutput("tcl.com v1.0 (c) 2025 Pedro de Medeiros\r\n$");
        DOS_StringOutput("No arguments provided.\r\n\r\n$");
        DOS_StringOutput("Usage: tcl <Tcl command to execute>.\r\n$");
        DOS_StringOutput("tcl returns text data.$");
        DOS_Exit0();
    }

    flat(argc, argv);

    // populate tcl_data and send to tcl_bridge
    int arg_len = String_Length(argv[0]);
    int cmd_len = String_Length(cmd_buf);
    Mem_Copy(argv[0], cmd_buf + cmd_len, arg_len);
    cmd_buf[cmd_len + arg_len + 0] = ']';
    cmd_buf[cmd_len + arg_len + 1] = '\0';
    tcl_data.cmd_addr     = cmd_buf;
    tcl_data.cmd_len      = cmd_len + arg_len + 1;
    tcl_data.res_addr     = cmd_buf;
    tcl_data.res_max_len  = RESPONSE_MAX;
    tcl_data.status       = 0x7F; // if this changes tcl_bridge is alive

    // Send command to Tcl engine
    tcl(&tcl_data); // here tcl_data fields are magically filled in...
    print_result();
    DOS_Exit(tcl_data.status);
}
