if command -v gcc >/dev/null 2>&1; then
    gcc -static cykompiler.c lex.c parse.c emit.c etc.c input.c -o cykompiler
else
    echo "GCC is not installed. Please install GCC to proceed."
    echo "Arch: sudo pacman -S gcc"
    echo "Debian/Ubuntu: sudo apt install gcc"
    echo "Fedora: sudo dnf install gcc"
    echo "macOS: brew install gcc"
    exit 1
fi

