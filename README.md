# Deduplicon
A demonic, open-source solution for absolute file control.

## Setup on windows

1. Install vcpkg (Step can be found at [here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell))
2. Install Openssl : `vcpkg install openssl`

## Build on Windows

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"
cmake --build build
```

## Build on Linux
```bash
cmake -B build -S .
cmake --build build
``̀

