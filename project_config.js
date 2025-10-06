DoCompile       = true;
DoMake          = true;
EmulMachine     = false;
Emulator        = "/home/pedro/Projects/openmsx/openmsx/openmsx";
EmulExtraParam  = ` -script ${ToolsDir}script/openMSX/debugger_pvm.tcl `;
EmulExtraParam += " -script ./startup.tcl ";
LibModules      = [];

Debug = true;
DebugSymbols = true;
BuildLibrary = true;

ProjName = "tcl";
ProjModules = [ ProjName ];

