# Deduplicon
A demonic, open-source solution for absolute file control.

# Ingredients needed for windows surmmoners

At first, deamon invocation needs ingredients before doing it.
Here are the list of ingredient needed:
1. get a bit of git clone vcpkg (Scrolls can be found at https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell)
2. Find a Avatar of Openssl : `vcpkg install openssl`


# Ritual to invoke them

```bash
# Stay seat without talking, stay focus (deamon invokation is not a game !)
# Use your ouija board (perfered) or your keyboard to type this
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="<path to vcpkg>/scripts/buildsystems/vcpkg.cmake"
cmake --build build
```

Once these incantations done, you should be able to command deamons.

# Powers granted to you

Congratulations !

You have now be granted to use daemon's power to control files.

