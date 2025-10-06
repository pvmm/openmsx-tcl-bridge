//*****************************************************************************
// PROJECT CONFIG OVERWRITE
//*****************************************************************************

//-- Target MSX machine version (string)
Machine = "2P";

//-- Target program format (string)
Target = "DOS1";

//-- Parse MSX-DOS command-line arguments
DOSParseArg = true;

//-- List of library modules to build (array)
LibModules = ["dos", "debug", "print", "vdp", ...LibModules];

//-- List of data files to copy to disk (array)
DiskFiles = [];

//-- Size of the final disk (.DSK file). Can be "360K" or "720K" (string)
DiskSize = "360K";

//-- Application ID. Can be 2 character string or 16-bits integer (0~65535)
AppID = "DO";
