/**
 * -----------------------------------------------------------------------------
 * Resource.cpp
 * -----------------------------------------------------------------------------
 */
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "json.hpp"

#include "common.hpp"
#include "Resource.hpp"




/**
 * TODO: UNUSED
 */
void Resource::loadConfig(const char *path)
{
    // loadJSON(path);
}




TextureMap Resource::loadTextures()
{
    using namespace std;
    using nlohmann::json;

    TextureMap texMap;

    // load png
    Texture2D atlas = LoadTexture("resources/production/textures.png");
    
    // load json
    ifstream i("resources/production/textures.json");

    // put data into json struct
    json j;
    i >> j;
    // // write prettified json
    // cout
    // // << setw(4) << j
    // << endl;
    auto frames = j["frames"];

    for (auto frame = frames.begin(); frame != frames.end(); ++frame) {
        string key = frame.key();
        auto f = frame.value()["frame"];

        auto x = f["x"];
        auto y = f["y"];
        auto w = f["w"];
        auto h = f["h"];
        // std::cout << frame.key() << " : " << frame.value() << "\n";
        // std::cout << "x: " << x << " y: " << y << " w: " << w << " h: " <<  h  << "\n" << endl;

        TextureData td;
        td.key = key;
        td.tex = atlas;
        td.srcFrame = Rectf(x, y, w, h);

        TextureMapEntry entry(key, td);

        texMap.insert(entry);
    }

    // for (auto& entry : texMap)
    // {
    //     // TODO: switch to log printing?
    //     cout
    //     << "TextureData loaded: "
    //     << entry.first 
    //     << endl;
    // }

    return texMap;
}

