# vforvector
A few day challenge
# Notes
- Licensed under the MIT License. 
- See dependencies `glm`, `glad`, `glfw` licenses on their respective sites.
- Noto Font license (not by me) found in `assets/Font/` directory
- A 3d model is needed in `./assets/3dmodel/logo.obj`, as well as the texture file (hard-coded) `./assets/3dmodel/Yes.png`.
- This is woefully incomplete, Highscores and questions are not working properly and the code has some questionable design
practices. It was completed in a few days, what can I say?

## Compilation
`CMake` is required to compile the program, as well as a C++ compiler.
Note that I have not tested compilation on Windows/Mac machines, although in theory it should work, and if not, it should with minor modifications.

### Native build
```
mkdir build
cmake -S . -B build
cmake --build build
```
### Emscripten build
Note that you need emscripten installed.  

Replace `/path_to_emscripten/emscripten` with the actual path to emscripten.  

Also note that I have only tried to build it in a Linux machine.
```
mkdir emscripten_build
cmake -DCMAKE_TOOLCHAIN_FILE=/path_to_emscripten/emscripten/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake  -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -S . -B emscripten_build
cmake --build emscripten_build
```
