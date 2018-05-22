/**
 * -----------------------------------------------------------------------------
 * renderer.hpp
 * -----------------------------------------------------------------------------
 */
#pragma once


#include "common.hpp"
#include "State.hpp"
#include "Resource.hpp"



class Renderer
{
public:
    TextureMap texMap;

    Color bgColor = { 25, 25, 25, 255 };
    Camera2D camera;
    bool zoomCamera = true;
    float zoomAmount = 0.5;
    float platformRenderScale;

    // constructor
    Renderer()
    {
        printlog(0, "creating Renderer\n");
        
        this->camera.target = rlVec2(0, 0);
        this->camera.offset = rlVec2( 0, 0 );
        this->camera.rotation = 0;
        // this->camera.zoom = 1;    

    #if defined(PLATFORM_WEB)
        this->platformRenderScale = 2.0;
    #else
        this->platformRenderScale = 1.0;
    #endif
    }

    virtual ~Renderer()
    {
        printlog(0, "destroying Renderer\n");
    }

    void init();
    void render(State *state);
    void renderEntities(State *state);
    void renderGui(State *state);
};