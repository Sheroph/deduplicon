# Deduplicon
A demonic, open-source solution for absolute file control.
It is a tool to keep a look on deplication ratio of a directory.
`Deduplicon` keep a track on what happens on monitored directory and update duplicate status.
It will be done for main OSes: Linux, Windows and MacOS.
Compilation tool used is `CMake` and C++ version is C++ 17

## Architecture

`Deduplicon` is split into three parts: `daemonarch`, `hashtaroth` and `beelzebase`.
Each modules provide a service and are decoupled between them.

The entry point of `deduplicon` is `daemonarch`, which monitor filesystem event on provided directory.
On each event, it notifies `beelzebase`, which is reponsible to store and duplication status of monitored directory.
`Beelzebase` can ask for file hashes to hashtaroth, which produces on demand hashes of files.

Third parties dependencies are :
- `openssl` use by module for hashing files

### daemonarch
This module provides a way to monitor filesystem events like adding, modifying, moving or deleting files or directory.
On linux, it uses inotify API.
On Windows, it is not implemented yet but will be.

### hashtaroth
It provides a convenient way to compute hashes of file, it can be seen as a hash service.
Hash computing is based upon openssl API.

### beelzebase
Persistent recording part of `deduplicon`, its role is to store deplication status of monitored items (file, directories).

## Windows

1. Install vcpkg (Step can be found at [here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell))
2. Install Openssl : `vcpkg install openssl`

### Build on Windows

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"
cmake --build build
```

## Build on Linux
```bash
cmake -B build -S .
cmake --build build
```

## Implementation status

For the moment, linux version is under developpment.
Native compiler will be used under each target OSes.
Gcc or clang for linux
clang for MacOS
MSVC for Windows (other compiler will be added, like clang)

One goal is to provide a way to use clang on each platform.

### Hashtaroth:
- Multiplatform, asynchronous, tested on Linux
- Implement multi-thread hashes processing

### Daemonarch
- Basic filesystem watcher on Linux is running

### Beelzebase
- Basic monitored filesystem entries stored on database throught sqlite3 on Linux