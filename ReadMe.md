# Example Building Boost with Emscripten and Conan

This example shows how to compile and use boost with Emscripten through the Conan dependency manager.
The main source of how to configure for using Emscripten is found in the [Conan docs](https://docs.conan.io/en/latest/integrations/cross_platform/emscripten.html).
While the official docs are using the Emscripten toolchain through Conan, this example treats it as an external entity as at the time of writing Emscripten 2.0 was not available in Conan.

## Conan Profile

In order to build Boost with only compatible moduldes, the following profile is used

```
include(default)
[settings]
os=Emscripten
arch=wasm
compiler=clang
compiler.version=12
compiler.libcxx=libc++
compiler.cppstd=14
[options]
boost:extra_b2_flags=target-os=linux
boost:without_fiber=True
boost:without_graph=True
boost:without_locale=True
boost:without_log=True
boost:without_mpi=True
boost:without_python=True
boost:without_regex=True
boost:without_stacktrace=True
boost:without_test=True
boost:zlib=False
boost:bzip2=False
boost:lzma=False
boost:zstd=False
```

## Steps

In order to support Emscripten 2.0, it necessary to patch the Boost build system. In `tools/build/src/tools/emscripten.jam` the archive action need the additional parameter `-r` to tell Emscripten to crate a static libary instead of an executable:

```
actions archive
{
    "$(CONFIG_COMMAND)" $(AROPTIONS) -r -o "$(<)" "$(>)"
}
```

1. Setup the Emscripten environment

```
$EmscriptenSdk=...
$EmscriptenSdk/emsdk_env.ps1
```

2. Build Boost and the test program 

```
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="$EmscriptenSdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" -DCMAKE_BUILD_TYPE=Release ..
```

3. Run the executable in NodeJS

```
node --experimental-wasm-threads --experimental-wasm-bulk-memory bin/conan_boost.js
```