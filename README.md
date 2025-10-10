![Screenshot](images/screenshot.png "Screenshot")

openmsx-tcl-bridge
==================

Guest machine side of mechanism that connects MSX-DOS to OpenMSX Tcl environment. This program uses a watchpoint to send responses back from Tcl to MSX-DOS, so it requires at least OpenMSX version 21.0.

How to use it
-------------

The **tcl.com** MSX-DOS program requires the **tcl_bridge.tcl** script on OpenMSX side to execute Tcl commands received by the program. Execute:
```
tcl_bridge start
```
on the Tcl console to connect the sending data port on the MSX side (port#6). Now you can for instance call:
```
tcl puts "Hello world"
```
on MSX-DOS command line to print "Hello world" on openMSX Tcl console, but you can use it to call `diskmanipulator` and automate stuff using OpenMSX. The sky is the limit!

To close the bridge, just execute:
```
tcl_bridge stop
```

How to compile it
-----------------

Just throw the directory inside a normal [MSXgl](https://github.com/aoineko-fr/MSXgl) install, specifically in the **projects** subdirectory, then call:
```
build.sh
```
If you want to compile a version of tcl.com that automatically transforms `\n` into `\r\n` to output the results to MSX-DOS screen, call:
```
build.sh define=TEXT_MODE
```
then it will automatically wrap any command with `string map [\n \r\n] [<command>]` and use Tcl itself to convert the response before sending it to the MSX.

The resulting binary will be inside the **out** subdirectory.

Related links
-------------

* The PR in OpenMSX of the Tcl script that completes the mechanism:
  * https://github.com/openMSX/openMSX/pull/1985
