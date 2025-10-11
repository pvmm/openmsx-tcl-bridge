#!/bin/bash
if type -P node; then
	node ../../engine/script/js/build.js projname=tcb target=DOS2 "$@"
	node ../../engine/script/js/build.js projname=tcl target=DOS2 define=FORCE_TEXT_MODE "$@"
else
	../../tools/build/Node/node ../../engine/script/js/build.js projname=tcb target=DOS2 "$@"
	../../tools/build/Node/node ../../engine/script/js/build.js projname=tcl target=DOS2 define=FORCE_TEXT_MODE "$@"
fi
