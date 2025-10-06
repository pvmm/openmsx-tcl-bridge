#!/bin/bash
# ____________________________
# ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄
# ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
# █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
# ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
#  by Guillaume 'Aoineko' Blanchard under CC BY-SA license
#────────────────────────────────────────────────────────────────────

DoRun="false"

build() {
    if type -P node; then
        node ../../engine/script/js/build.js projname=tcl "$@"
    else
        ../../tools/build/Node/node ../../engine/script/js/build.js projname=tcl "$@"
    fi
}

while true; do
    clear
    echo "===== Select build procedure ====="
    echo "1) Clean"
    echo "2) Make MSX-DOS1 app"
    echo "3) Make MSX-DOS2 app"
    echo "4) Toggle DoRun ($DoRun)"
    echo "5) Exit"
    echo "====================="
    read -p "Select an option [1-4]: " choice

    case $choice in
        1)
            build clean
            read -p "Press any key..."
            ;;
        2)
            build clean
            if [ "$DoRun" = true ]; then
                build target=DOS1 run
            else
                build target=DOS1
            fi
            read -p "Press any key..."
            ;;
        3)
            build clean
            if [ "$DoRun" = true ]; then
                build target=DOS2 run
            else
                build target=DOS2
            fi
            read -p "Press any key..."
            ;;
        4)
            if [ "$DoRun" = true ]; then
                DoRun=false
            else
                DoRun=true
            fi
            ;;
        5)
            echo "Goodbye!"
            break
            ;;
        *)
            echo "Invalid option, please try again."
            ;;
    esac

    echo    # blank line for readability
done
