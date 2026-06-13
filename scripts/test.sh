#!/bin/bash

#kill any orphan server processes
pkill server

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

"$PROJECT_DIR/build/bin/server/server" &

for arg in "$@"; do
    kitty bash -c "\"$PROJECT_DIR/build/bin/client/client\" \"$arg\"; exec bash" &
done
