#ifndef _COMMON_H_
#define _COMMON_H_

#include "msxgl.h"
#include "dos.h"
#include "string.h"

// Data to send to tcl_bridge
struct tcl_data {
    c8* cmd_addr;       // offset + 0
    u16 cmd_len;        // offset + 2
    c8* res_addr;       // offset + 4
    u16 res_max_len;    // offset + 6
    u16 res_real_len;   // offset + 8
    i8  status;         // offset + 10
};

extern struct tcl_data tcl_data;

// RESPONSE_MAX uses memory after program's end, so it can use much more memory
#define RESPONSE_MAX 30000

void tcl(void* data);

void print(c8* buffer, u16 length);

void flat(u8 argc, c8** argv);

void print_result();

#endif // _COMMON_H_
