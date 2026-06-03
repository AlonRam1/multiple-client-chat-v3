#!/bin/bash

./build/bin/server/server &

for arg in "$@"; do
    kitty bash -c "./build/bin/client/client \"$arg\"; exec bash" &
done
