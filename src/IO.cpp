#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// #include <cJSON/cJSON.h>
#include "json.hpp"

#include "common.hpp"
#include "IO.hpp"




/**
 * TODO
 */
void IO::loadConfig(const char *path)
{
    // loadJSON(path);
}


char *IO::loadFileBuffer(const char *path)
{
    char *buffer = 0;
    long length;
    FILE * f = fopen(path, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell (f);
        fseek(f, 0, SEEK_SET);

        buffer = (char *)malloc(length);

        if (!buffer) {
            perror("error opening file");
            exit(1);
        }

        fread(buffer, 1, length, f);        
        fclose(f);
    }

    return buffer;
}


void IO::loadJSON(const char *path)
{
    using namespace std;
    using nlohmann::json;

    println("loading '%s'... \n", path);
    

    // open file
    ifstream i(path);

    // put data into json
    json j;
    i >> j;

    auto frames = j["frames"];

    for (auto frame = frames.begin(); frame != frames.end(); ++frame) {
        auto f = frame.value()["frame"];
        int x = f["x"];
        int y = f["y"];
        int w = f["w"];
        int h = f["h"];
        std::cout << frame.key() << " : " << frame.value() << "\n";
        std::cout << "x: " << x << " y: " << y << " w: " << w << " h: " <<  h  << "\n" << endl;
    }

    // for (auto &n : nums)
    // {
    //     cout
    //     << n
    //     << endl;
    // }

    // // write prettified json
    // cout
    // // << setw(4) << j
    // << j
    // << endl;
}

