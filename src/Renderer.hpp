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

    Color mBGColor;

    Camera2D mCamera;
    bool zoomCamera;
    float zoomAmount;

    float platformRenderScale;

    // constructor
    Renderer()
    {
        printlog(0, "creating Renderer\n");
        
        this->mBGColor = (Color){
            25, 25, 25, 255
        };

        this->mCamera.target = rlVec2(0, 0);
        this->mCamera.offset = rlVec2(
            0, 0
            // -s->screenWidth / 2.0,
            // -s->screenHeight / 2.0
        );
        this->mCamera.rotation = 0;
        // this->mCamera.zoom = 1;    

        this->zoomCamera = true;
        this->zoomAmount = 0.5;

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