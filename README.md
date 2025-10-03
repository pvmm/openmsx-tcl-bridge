![Screenshot](images/screenshot.png "Screenshot")

openmsx-tcl-bridge
==================

Guest machine side of mechanism that connects guest machine to OpenMSX through Tcl environment. This program uses the **Programmable Device** extension to send responses back from Tcl to MSX-DOS, so it requires at least OpenMSX version 21.0.

How to use it
-------------

The tcl.com MSX-DOS program requires the **tcl_bridge.tcl** script on OpenMSX side to execute Tcl commands received by the program. Execute:
```
tcl_bridge start
```
on the Tcl console to connect the receiving and sending ports on the MSX side (ports 6 and 7 respectively). Now you can call:
```tcl puts Hello world```
On MSX-DOS command line to send Tcl commands to openMSX. To close the bridge, execute:
```
tcl_bridge stop
```
