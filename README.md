Build Instructions
------------------
- Clone repo & submodules: `git clone --recurse-submodules https://github.com/ENAML/flappy.git`

[TODO]


TODO 
-----
## Main
- [x] Add score rendering
- [ ] Clean up codebase
- [ ] Move forked version of raylib into project 
- [ ] Add better logging
    - see: https://github.com/gabime/spdlog 
- [ ] 

## Web Compile
- [ ] Clean up Makefile emscripten compilation
- [ ] Add closure compiler for emscripten
- [ ] Make new index.html
- [ ] Figure out how to set canvas size from C++ / makefile config 

## Nice-to-have
- [ ] Look into moving Vector/Matrix stuff to `GLM` from code in `Utility`
    - main site: https://glm.g-truc.net/0.9.8/index.html
    - (docs / examples): https://glm.g-truc.net/0.9.2/api/index.html
- [ ] Add title screen
- [ ] Add game-over screen
- [ ] Add particle fx


Building for Web
----------------
## Instructions
- 1) Download and install emscripten (http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
- 2) run `source ./emsdk_env.sh` from `emsdk/` directory to set environment variables
    - ex: `source ~/Projects/tests/emsdk/emsdk_env.sh`
- 3) build RayLib for html5
    - `cd raylib/src`
    - `make PLATFORM=PLATFORM_WEB`
    - NOTE: might need to modify Makefile (I had to remove everything under `#Emscripten required variables`)
- 4) within our own Makefile, set correct paths for `EMSCRIPTEN_PATH` (to `emsdk/` emscripten director) and `RAYLIB_PATH` (to `raylib` director)
- 5) run `make web`
- 6) if successful, .html / .js / .data files should be in `bin/`

## NOTES
- Reducing emscripten output size:
    - https://hacks.mozilla.org/2018/01/shrinking-webassembly-and-javascript-code-sizes-in-emscripten/


C++ Refs
--------
## Lambda functions
- http://www.cplusplus.com/reference/algorithm/remove_if/
- https://studiofreya.com/cpp/std-remove_if-with-lambda/
- https://shaharmike.com/cpp/lambdas-and-functions/ 

## Rust-Style Pattern Matching / Discrimited Unions / Variants
- (SEEMS LIKE BEST OPTION): https://github.com/solodon4/Mach7
- https://genbattle.bitbucket.io/blog/2016/10/07/Type-Safe-Unions-in-C-and-Rust/
- seems like a good option for using them in c++: https://github.com/mapbox/variant
    - also list some other options: https://github.com/mapbox/variant/blob/master/doc/other_implementations.md
- https://github.com/martinmoene/variant-lite

# Make / Makefile Stuff
- http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
- http://itscompiling.eu/2017/01/12/precompiled-headers-cpp-compilation/ 
