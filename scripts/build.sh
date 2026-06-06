#!/bin/bash
mkdir -p build
cmake -S . -B build/cmake
cmake --build build/cmake
printf '\n\n\n'
echo "chat program built successfully! now to run it run server and client scripts from the script directory, or run the test script from there (see README)."
