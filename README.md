

# ----
# TODO 
# ----

# Replace mapbox::variant with Mach7
- https://github.com/solodon4/Mach7

# Look into moving Vector/Matrix stuff to `GLM` from code in `Utility`
- main site: https://glm.g-truc.net/0.9.8/index.html
- (docs / examples): https://glm.g-truc.net/0.9.2/api/index.html

# Look into `pre-compiled` header/cpp files from a SINGLE source?
- LazyCplusPlus ?
    - http://www.lazycplusplus.com/ 
- Buck / Buckaroo ?
    - https://hackernoon.com/generating-a-single-include-c-header-file-using-buck-827f20be3f9d
- MakeHeaders ?
    - https://www.hwaci.com/sw/mkhdr/
- see: https://softwareengineering.stackexchange.com/questions/35375/what-to-do-if-i-hate-c-header-files

# SVG / Vector / Path Utils
- Figure out way to either RENDER svgs with C++ or CONVERT them to PNG
    - https://github.com/memononen/nanosvg
    - https://github.com/mapbox/earcut.hpp
    - https://github.com/memononen/nanovg
- Tools for editing svgs
    - http://editor.method.ac/ 
    - https://github.com/SVG-Edit/svgedit
    - https://github.com/bigtimebuddy/pixi-svg
    - https://two.js.org/examples/
    - https://github.com/nical/lyon


# ----------------
# Building for Web
# ----------------

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


# --------
# C++ Refs
# --------

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

# Hungarian Notation
- https://stackoverflow.com/questions/1228161/why-use-prefixes-on-member-variables-in-c-classes
basically:
- `m` for members
- `c` for constants/readonlys
- `p` for pointer (and `pp` for pointer to pointer)
- `v` for volatile
- `s` for static
- `i` for indexes and iterators
- `e` for events 


# -------------
# GameDev stuff
# -------------

## Useful resources for 2d platformers / physics / etc
- Best article on the topic : https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-guide-to-implementing-2d-platformers-r2936/
- Super simple but good start: http://jonathanwhiting.com/tutorial/collision/
- https://gamedevelopment.tutsplus.com/tutorials/basic-2d-platformer-physics-part-1--cms-25799 
- http://www.metanetsoftware.com/dev/tutorials 
- (esp. part 1 & 2) http://web.archive.org/web/20090523104747/http://jnrdev.72dpiarmy.com/
- https://github.com/aloisdeniel/Humper 
- https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084

- https://gamedev.stackexchange.com/questions/18302/2d-platformer-collisions
- https://gamedev.stackexchange.com/questions/116616/2d-platformer-aabb-collision-issues 
- https://gamedev.stackexchange.com/questions/14486/2d-platformer-aabb-collision-problems?noredirect=1&lq=1 

## More complex collision detection / response
- https://katyscode.wordpress.com/2013/01/18/2d-platform-games-collision-detection-for-dummies/
- http://www.metanetsoftware.com/dev/tutorials
- https://gamedev.stackexchange.com/questions/13004/where-should-collision-detection-logic-be-placed
- https://wildbunny.co.uk/blog/2011/03/25/speculative-contacts-an-continuous-collision-engine-approach-part-1/

## shmup resources
- https://gamedevelopment.tutsplus.com/series/cross-platform-vector-shooter-ios--cms-560
- http://fabiensanglard.net/Prototyp/index.php
- https://github.com/fabiensanglard/Prototype
- https://github.com/fabiensanglard/Shmup 
- 