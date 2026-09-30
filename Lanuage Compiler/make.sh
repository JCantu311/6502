#!/bin/bash
if [ ! -d ./bin ]; then
    mkdir ./bin
    ./make.sh
else 
    if command -v gcc >/dev/null 2>&1; then
        # Check if the OS is macOS
        if [ "$(uname)" = "Darwin" ]; then
            echo "Building for macOS (Dynamic linking)..."
            gcc cykompiler.c lex.c parse.c emit.c etc.c input.c -o ./bin/cykompiler
        else
            echo "Building for Linux (Static linking)..."
            gcc -static cykompiler.c lex.c parse.c emit.c etc.c input.c -o ./bin/cykompiler
        fi
    else
        echo "GCC is not installed. Please install GCC to proceed."
        echo "Arch: sudo pacman -S gcc"
        echo "Debian/Ubuntu: sudo apt install gcc"
        echo "Fedora: sudo dnf install gcc"
        echo "macOS: brew install gcc"
        exit 1
    fi
fi
