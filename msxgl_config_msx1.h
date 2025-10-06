// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
//  Library configuration
//─────────────────────────────────────────────────────────────────────────────
#pragma once

//-----------------------------------------------------------------------------
// BUILD
//-----------------------------------------------------------------------------

// Target
// - TARGET_ROM_8K					8 KB ROM in page 1 (4000h ~ 5FFFh)
// - TARGET_ROM_8K_P2				8 KB ROM in page 2 (8000h ~ 9FFFh)
// - TARGET_ROM_16K					16 KB ROM in page 1 (4000h ~ 7FFFh)
// - TARGET_ROM_16K_P2				16 KB ROM in page 2 (8000h ~ BFFFh)
// - TARGET_ROM_32K					32 KB ROM in page 1&2 (4000h ~ BFFFh)
// - TARGET_ROM_48K					48 KB ROM in page 0-2 (0000h ~ BFFFh)
// - TARGET_ROM_48K_ISR				48 KB ROM in page 0-2 (0000h ~ BFFFh) with ISR replacement
// - TARGET_ROM_64K					64 KB ROM in page 0-3 (0000h ~ FFFFh)
// - TARGET_ROM_64K_ISR				64 KB ROM in page 0-3 (0000h ~ FFFFh) with ISR replacement
// - TARGET_ROM_ASCII8				ASCII-8: 8KB segments for a total of 64 KB to 2 MB
// - TARGET_ROM_ASCII16				ASCII-16: 16KB segments for a total of 64 KB to 4 MB
// - TARGET_ROM_KONAMI				Konami MegaROM (aka Konami4): 8 KB segments for a total of 64 KB to 2 MB
// - TARGET_ROM_KONAMI_SCC			Konami MegaROM SCC (aka Konami5): 8 KB segments for a total of 64 KB to 2 MB
// - TARGET_DOS1					MSX-DOS 1 program (starting at 0100h)
// - TARGET_DOS2					MSX-DOS 2 program (starting at 0100h)
// - TARGET_DOS0					Direct program boot from disk (starting at 0100h)
// - TARGET_BIN						BASIC binary program (starting at 8000h)
// - TARGET_BIN_USR					BASIC USR binary driver (starting at C000h)
// TARGET is defined by the build tool

// MSX version
// - MSX_1 ........................ MSX1
// - MSX_2 ........................ MSX2
// - MSX_12 ....................... MSX1 and 2 (support each)
// - MSX_2K ....................... Korean MSX2 (SC9 support)
// - MSX_2P ....................... MSX2+
// - MSX_22P ...................... MSX2 and 2+ (support each)
// - MSX_122P ..................... MSX1, 2 and 2+ (support each)
// - MSX_0 ........................ MSX0 (MSX2+)
// - MSX_TR ....................... MSX turbo R
// - MSX_3 ........................ MSX3
// MSX_VERSION is defined by the build tool

//-----------------------------------------------------------------------------
// BIOS MODULE
//-----------------------------------------------------------------------------

// Default slot BIOS access
// - BIOS_CALL_DIRECT ............. Use direct access to Bios routines (ROM slot must be selected in corresponding page)
// - BIOS_CALL_INTERSLOT .......... Use inter-slot access to Bios routines (through CALSLT routine)
#define BIOS_CALL_MAINROM			BIOS_CALL_DIRECT
#define BIOS_CALL_SUBROM			BIOS_CALL_INTERSLOT
#define BIOS_CALL_DISKROM			BIOS_CALL_INTERSLOT

// MAIN-Bios module setting
#define BIOS_USE_MAINROM			TRUE	// Allow use of Main-ROM routines
#define BIOS_USE_VDP				TRUE	// Give access to Main-ROM routines related to VDP
#define BIOS_USE_PSG				TRUE	// Give access to Main-ROM routines related to PSG
#define BIOS_USE_SUBROM				TRUE	// Allow use of Sub-ROM routines (MSX2/2+/turbo R)
#define BIOS_USE_DISKROM			TRUE	// Allow use of Disk-ROM routines

//-----------------------------------------------------------------------------
// VDP MODULE
//-----------------------------------------------------------------------------

// VRAM addressing unit
// - VDP_VRAM_ADDR_14 ............. Use 14-bits 16K VRAM addressing for MSX1 (u16)
// - VDP_VRAM_ADDR_17 ............. Use 17-bits 128K VRAM addressing for MSX2/2+/turbo R (u32)
#define VDP_VRAM_ADDR				VDP_VRAM_ADDR_14

// VDP X/Y units
// - VDP_UNIT_U8 .................. X and Y use 8-bits values
// - VDP_UNIT_X16 ................. X use 16-bits and Y use 8-bits values
// - VDP_UNIT_Y16 ................. X use 8-bits and Y use 16-bits values
// - VDP_UNIT_U16 ................. X and Y use 16-bits values
#define VDP_UNIT					VDP_UNIT_U8

// VDP screen modes (additionnal limitations come from the selected MSX_VERSION)
#define VDP_USE_MODE_T1				TRUE	// MSX1		Screen 0 Width 40
#define VDP_USE_MODE_G1				TRUE	// MSX1		Screen 1
#define VDP_USE_MODE_G2				TRUE	// MSX1		Screen 2
#define VDP_USE_MODE_MC				TRUE	// MSX1		Screen 3
#define VDP_USE_MODE_T2				FALSE	// MSX2		Screen 0 Width 80
#define VDP_USE_MODE_G3				FALSE	// MSX2		Screen 4
#define VDP_USE_MODE_G4				FALSE	// MSX2		Screen 5
#define VDP_USE_MODE_G5				FALSE	// MSX2		Screen 6
#define VDP_USE_MODE_G6				FALSE	// MSX2		Screen 7
#define VDP_USE_MODE_G7				FALSE	// MSX2/2+	Screen 8, 10, 11 & 12

#define VDP_USE_VRAM16K				TRUE	// Use 16K VRAM access functions on MSX2
#define VDP_USE_SPRITE				TRUE	// Use sprite handling functions
#define VDP_USE_COMMAND				TRUE	// Use VDP commands wrapper functions
#define VDP_USE_CUSTOM_CMD			FALSE	// Use custom VDP commands through data buffer
#define VDP_AUTO_INIT				TRUE	// Call VDP_Initialize() at the first call to VDP_SetMode()
#define VDP_USE_UNDOCUMENTED		TRUE	// Allow the use of undocumented screen mode (WIP)
#define VDP_USE_VALIDATOR			TRUE	// Handle some option specific for each VDP mode (highly recommended)
#define VDP_USE_DEFAULT_PALETTE		FALSE	// Add data for default MSX2 palette
#define VDP_USE_MSX1_PALETTE		FALSE	// Add data for default MSX1 palette
#define VDP_USE_DEFAULT_SETTINGS	TRUE	// Auto-initialization of common VDP feature
#define VDP_USE_16X16_SPRITE		TRUE	// Use 16x16 sprites mode
#define VDP_USE_RESTORE_S0			TRUE	// Do restore of status register pointer to S#0 (needed onlt for default BIOS ISR)
#define VDP_USE_PALETTE16			TRUE	// Use 16 entries palette (use only 15 entries otherwise)

// ISR protection while modifiying VDP registers
// - VDP_ISR_SAFE_NONE ............ No ISR protection (for program not using VDP interruption)
// - VDP_ISR_SAFE_DEFAULT ......... Protect only VDP register pair writing (default behavior; ISR can read/write registers but VRAM ones)
// - VDP_ISR_SAFE_ALL ............. Protect all VDP writing process
#define VDP_ISR_SAFE_MODE			VDP_ISR_SAFE_DEFAULT

// Initial screen mode setting
// - VDP_INIT_OFF ................. Force option to be disable
// - VDP_INIT_ON .................. Force option to be enable
// - VDP_INIT_AUTO ................ Determining the best value for the context
// - VDP_INIT_DEFAULT ............. Keep default value

//-----------------------------------------------------------------------------
// PRINT MODULE
//-----------------------------------------------------------------------------

// Print module setting
#define PRINT_USE_TEXT				TRUE	// Allow use of Text font (T1-T2, G1-G3)

//-----------------------------------------------------------------------------
// DEBUG & PROFILE
//-----------------------------------------------------------------------------

// Debugger options
// - DEBUG_DISABLE ................ No debug tool
// - DEBUG_EMULICIOUS ............. Debug features for Emulicious
// - DEBUG_OPENMSX ................ Debug features for openMSX using 'debugdevice' extension
// - DEBUG_OPENMSX_P .............. Debug features for openMSX using PVM script (tools/script/openMSX/debugger_pvm.tcl)
#define DEBUG_TOOL DEBUG_OPENMSX_P
// Profiler options
// - PROFILE_DISABLE .............. No profile tool
// - PROFILE_OPENMSX_G ............ Profiler features for openMSX using Grauw script (tools/script/openMSX/profiler_grauw.tcl)
// - PROFILE_OPENMSX_S ............ Profiler features for openMSX using Salutte script (tools/script/openMSX/profiler_salutte.tcl)
#define PROFILE_TOOL                            PROFILE_DISABLE
#define PROFILE_LEVEL                           10
