#!/bin/bash

#kill any orphan server processes
pkill server

./build/bin/server/server &

for arg in "$@"; do
    kitty bash -c "./build/bin/client/client \"$arg\"; exec bash" &
done
