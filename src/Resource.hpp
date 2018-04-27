/**
 * -----------------------------------------------------------------------------
 * Resource loading / handling
 * -----------------------------------------------------------------------------
 */
#pragma once

#include <string>
#include <unordered_map>

#include "common.hpp"


/**
 * Resource types
 * --------------
 */

struct TextureData
{
    std::string key;
    Texture2D tex;
    Rectf srcFrame;
};
using TextureMap = std::unordered_map<std::string, TextureData>;
using TextureMapEntry = std::pair<std::string, TextureData>;


/**
 * Resource handling functions
 * ---------------------------
 */
class Resource
{
public:
    static void loadConfig(const char *path);
    static TextureMap loadTextures();
};