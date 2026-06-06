## Multiple Client Chat V3

this is the third iteration of my own multiple client chat. It's purpose is to implement a professional chat program using grpc.

## Features
>Bi-directional gRPC streaming.
>Multiple clients per-chat.
>real time server notifications on users.
>Thread-safe client management.

## Technologies used
>C++23
>gRPC 3.20
>protobuf
>CMake

## building

to build the program, simply run './scripts/build.sh' from the root folder.

## running

to run the program, run './scripts/server.sh' and './scripts/client.sh' respectively from the root directory.
keep in mind that you can give client.sh one argument representing a username, which allows you to skip entering a username upon running the client.

if you want a quick test setup, run './scripts/test.sh' from the root directory. the script takes a list of names as arguments, and opens a server + clients with the given usernames.
