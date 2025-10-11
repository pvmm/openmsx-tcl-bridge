// tcb.com v1.0 (c) 2025 Pedro de Medeiros
//
// tcb.com implements tcl_bridge as a reference implementation and returns
// binary data from the Tcl interface.
//
// tcb.com implements tcl_bridge as a reference implementation.
// tcl.com treats result from Tcl as binary data.

#include "common.h"
#include "tcl_cmd.h"

void main(u8 argc, c8** argv)
{
    if (argc < 1) {
        DOS_StringOutput("tcb.com v1.0 (c) 2025 Pedro de Medeiros\r\n$");
        DOS_StringOutput("No arguments provided.\r\n\r\n$");
        DOS_StringOutput("Usage: tcb <Tcl command to execute>.\r\n$");
        DOS_StringOutput("tcb returns unprocessed binary data.$");
        DOS_Exit0();
    }

    flat(argc, argv);

    // populate tcl_data and send to tcl_bridge
    int arg_len = String_Length(argv[0]);
    tcl_data.cmd_addr     = argv[0];
    tcl_data.cmd_len      = String_Length(argv[0]);
    tcl_data.res_addr     = cmd_buf;
    tcl_data.res_max_len  = RESPONSE_MAX;
    tcl_data.status       = 0x7F; // if this changes tcl_bridge is alive

    // Send command to Tcl engine
    tcl(&tcl_data); // here tcl_data fields are magically filled in...

    print_result();
    DOS_Exit(tcl_data.status);
}
