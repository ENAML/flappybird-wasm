TODO 
-----

## Main
- [ ] Upgrade Raylib version to 2.*
- [ ] Add better logging
    - see: https://github.com/gabime/spdlog 
- [x] Add score rendering
- [x] Clean up codebase

## Web Compile
- [ ] Clean up Makefile emscripten compilation
- [ ] Make new index.html
- [ ] Figure out how to set canvas size from C++ / makefile config 
- [x] Add closure compiler for emscripten
- [x] Add WASM support

## Nice-to-have
- [ ] Add title screen
- [ ] Add game-over screen
- [ ] Add particle fx
- [ ] Set up CMake / Premake for project
- [ ] Look into moving Vector/Matrix stuff to `GLM` from code in `Utility`
    - main site: https://glm.g-truc.net/0.9.8/index.html
    - (docs / examples): https://glm.g-truc.net/0.9.2/api/index.html


Build Instructions
------------------
- Clone repo & submodules: `git clone --recurse-submodules https://github.com/ENAML/flappy.git`
- build raylib (if necessary):
- Build for desktop (OSX)
    - `brew install raylib`
    - `make`
- Build for web
    - If emscriten bytecode needs to be rebuilt
        - `cd extern/raylib/src; make PLATFORM=PLATFORM_WEB` 
    - `make web`


Building for Web (TODO: deprecated)
-------------------------------------

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

