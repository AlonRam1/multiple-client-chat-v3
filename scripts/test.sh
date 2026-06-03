#!/bin/bash

./build/bin/server/server &

sleep 5

for arg in "$@"; do
    kitty bash -c "./build/bin/client/client \"$arg\"; exec bash" &
    sleep 5
done
