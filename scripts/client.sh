#!/usr/bin/env bash

if [ $# -eq 1 ]; then
    ./build/bin/client/client "$1"
else
    ./build/bin/client/client
fi
