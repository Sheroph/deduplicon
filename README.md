# Deduplicon
A demonic, open-source solution for absolute file control.

# Ingredients needed for windows surmmoners

At first, deamon invocation needs ingredients before doing it.
Here are the steps to prepare summoning :
1. Install vcpkg (Step can be found at [here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell))
2. Install Openssl : `vcpkg install openssl`


# Ritual to invoke them

```bash
# Stay seat without talking, stay focus (deamon invokation is not a game !)
# Use your ouija board (perfered) or your keyboard to type this
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"
cmake --build build
```

Once these incantations done, you should be able to command deamons.

# Powers granted to you

Congratulations !

You have now be granted to use daemon's power to control files.

