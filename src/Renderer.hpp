/**
 * -----------------------------------------------------------------------------
 * Renderer
 * -----------------------------------------------------------------------------
 */
#pragma once

#include "rlgl.h"

#include "common.hpp"
#include "State.hpp"
#include "gui.h"

/*
    Draw a part of a texture (defined by a rectangle) with 'pro' parameters
    NOTE: origin is relative to destination rectangle size
    see: raylib's "DrawTexturePro()"
 */
void my_drawTexture(
    Texture2D texture,
    Rectf sourceRec,
    Rectf destRec,
    Vec2f origin = Vec2f(0),
    float rotation = 0,
    Color tint = WHITE
) {
    // Check if texture is valid
    if (texture.id > 0)
    {
        if (sourceRec.size.width < 0) sourceRec.position.x -= sourceRec.size.width;
        if (sourceRec.size.height < 0) sourceRec.position.y -= sourceRec.size.height;

        rlEnableTexture(texture.id);

        rlPushMatrix();
            rlTranslatef((float)destRec.position.x, (float)destRec.position.y, 0);
            rlRotatef(rotation, 0, 0, 1);
            rlTranslatef(-origin.x, -origin.y, 0);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer

                // Bottom-left corner for texture and quad
                rlTexCoord2f((float)sourceRec.position.x/texture.width, (float)sourceRec.position.y/texture.height);
                rlVertex2f(0.0f, 0.0f);

                // Bottom-right corner for texture and quad
                rlTexCoord2f((float)sourceRec.position.x/texture.width, (float)(sourceRec.position.y + sourceRec.size.height)/texture.height);
                rlVertex2f(0.0f, (float)destRec.size.height);

                // Top-right corner for texture and quad
                rlTexCoord2f((float)(sourceRec.position.x + sourceRec.size.width)/texture.width, (float)(sourceRec.position.y + sourceRec.size.height)/texture.height);
                rlVertex2f((float)destRec.size.width, (float)destRec.size.height);

                // Top-left corner for texture and quad
                rlTexCoord2f((float)(sourceRec.position.x + sourceRec.size.width)/texture.width, (float)sourceRec.position.y/texture.height);
                rlVertex2f((float)destRec.size.width, 0.0f);
            rlEnd();
        rlPopMatrix();

        rlDisableTexture();
    }
}


class Texture
{
    string key;
    Texture2D tex;
    Rectf srcFrame;
};

struct Textures
{
    Texture2D bird;
    Texture2D atlas;


};


class Renderer
{
    public:
    Textures mTextures;
    Color mBGColor;

    Camera2D mCamera;
    bool zoomCamera;
    float zoomAmount;

    float platformRenderScale;

    

    Renderer()
    {
        printlog(0, "creating Renderer\n");
        
        this->mBGColor = (Color){
            // 230, 230, 230, 255,
            // 0, 0, 0, 255
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

    void init()
    {
        // load textures

        this->mTextures.bird = LoadTexture("resources/flappy_assets/sprites/bluebird-downflap.png"); // 34 x 24

        this->mTextures.atlas = LoadTexture("util/tinypng/bin/atlas.png");
    }

    void render(State *state)
    {
        BeginDrawing();

        ClearBackground(this->mBGColor);

        /**
         * draw entities
         */
        this->renderEntities(state);
        

        /**
         * draw gui
         */
        if (state->guiVisible)
        {
            this->renderGui(state);
        }


        // complete render 
        EndDrawing();            
    }

    void renderEntities(State *state)
    {
        // set camera zoom (this affects everything that is rendered)
        this->mCamera.zoom = this->zoomCamera ? this->zoomAmount : 1.0;
        Begin2dMode(this->mCamera);

        const float DEBUG_OPACITY = 0.3;

        const Color BIRD_COLOR = (Color){255, 255, 255, 255};
        const Color PIPE_COLOR = (Color){255, 0, 113, 255};

        float zoomScale = (1.0 / this->mCamera.zoom) * this->platformRenderScale;
        // float scale = 1.0;


        auto draw_rect = [&](Vec2f position, Vec2f size, Color c)
        {
            DrawRectangle(
                (position.x) * zoomScale,
                (position.y) * zoomScale,
                size.x * zoomScale,
                size.y * zoomScale,
                c 
            );
        };
        auto draw_rect_centered = [&](Vec2f position, Vec2f size, Color c)
        {
            DrawRectangle(
                (position.x - size.x/2) * zoomScale,
                (position.y - size.y/2) * zoomScale,
                size.x * zoomScale,
                size.y * zoomScale,
                c 
            );
        };
        auto draw_circle = [&](Vec2f position, float radius, Color c)
        {
            DrawCircle(
                position.x * zoomScale,
                position.y * zoomScale,
                radius * zoomScale,
                c
            );
        };


        // draw pipes
        for (auto& pipe : state->gameState.pipes)
        {
            auto& gameState = state->gameState;

            auto xPos = pipe.x - gameState.xOffset;
            auto pipeSize = Vec2f(pipeWidth, pipeHeight);

            // draw top pipe
            auto topPos = Vec2f(xPos, pipe.y - halfGap - pipeHeight);
            draw_rect(
                topPos,
                pipeSize,
                PIPE_COLOR
            );

            // draw btm pipe
            auto btmPos = Vec2f(xPos, pipe.y + halfGap);
            draw_rect(
                btmPos,
                pipeSize,
                PIPE_COLOR
            );
        }

        // draw bird 
        draw_circle(
            Vec2f(birdX, state->gameState.birdY),
            birdSize,
            BIRD_COLOR
        );
        

        /**
         * TEST TEX RENDER
         * ---------------
         */ 
        static float rot = 0;

        // test with single sprite img
        {
            Texture2D tex = this->mTextures.bird;
            Rectf srcRect(0, 0, tex.width, tex.height);

            Vec2f position = Vec2f(100, 100) * zoomScale;
            Vec2f size = Vec2f(tex.width, tex.height) * zoomScale * 2;
            Rectf destRect(position, size);
            
            Vec2f offset(size / 2);
            my_drawTexture(
                tex,
                srcRect,
                destRect,
                offset,
                rot
            );
        }

        // test with atlas
        {
            Texture2D tex = this->mTextures.atlas;

            // atlas coords
            auto x = 0.5175857544 * tex.width;
            auto y = 0.1972732544 * tex.height;
            auto w = (0.5507736206 * tex.width) - x;
            auto h = (0.2206954956 * tex.height) - y;

            Rectf srcRect(x, y, w, h);

            Vec2f position = Vec2f(200, 100) * zoomScale;
            Vec2f size = Vec2f(w, h) * zoomScale * 2;
            Rectf destRect(position, size);
            
            Vec2f offset(size / 2);
            my_drawTexture(
                tex,
                srcRect,
                destRect,
                offset,
                rot
            );
        }

        rot++;



        



        // end camera 2d render
        End2dMode();
    }



    void renderGui(State *state)
    {
        // draw cursor sguff
        if (state->mouseDown)
        {
            // println("drawing cursor...");
            auto col = Fade(WHITE, 0.5);
            DrawCircle(state->mouseDragPos.x, state->mouseDragPos.y, 5, col);
            DrawCircle(state->mousePressedPos.x, state->mousePressedPos.y, 10, col);
        }


        static char guiTextBuf[1000];
        

        // int screenWidth = state->screenWidth;

        int heightText = 15;
        int heightBtn = 20;        
        int heightSlider = 15;        

        int padding = 10;
        int width = 100;
        // int x = screenWidth - width - padding;
        int x = padding;

        int yNext = padding;

        /**
         * draw background
         */
        DrawRectangle(0, 0, width + padding*2, 300, Fade(BLACK, 0.8));

        
        /**
         * render text
         */
        sprintf(guiTextBuf, "FPS: %i", state->fps);
        gui_label(
            (Rectangle){ x, yNext, width, heightText },
            guiTextBuf
        );
        yNext += heightText;


        yNext += padding;


        /**
         * render button
         */
        // char *btnTitle = "Can Update";
        sprintf(guiTextBuf, "Can Update");
        state->canUpdate = gui_toggleButton(
            (Rectangle){ x, yNext, width, heightBtn},
            guiTextBuf,
            state->canUpdate
        );
        // println("Can upd: %i\n", state->canUpdate);
        yNext += padding + heightBtn;

        /**
         * render button
         */
        // char *btnTitle = "Can Update";
        sprintf(guiTextBuf, "Debug Draw");
        state->debugDraw = gui_toggleButton(
            (Rectangle){ x, yNext, width, heightBtn},
            guiTextBuf,
            state->debugDraw
        );
        // println("Can upd: %i\n", state->canUpdate);
        yNext += padding + heightBtn;


        /**
         * render button
         */
        sprintf(guiTextBuf, "Zoom Camera");
        this->zoomCamera = gui_toggleButton(
            (Rectangle){ x, yNext, width, heightBtn},
            guiTextBuf,
            this->zoomCamera 
        );
        yNext += padding + heightBtn;

        /**
         * render slider  
         */
        sprintf(guiTextBuf, "Zoom Amount: %.2f", this->zoomAmount);
        gui_label(
            (Rectangle){ x, yNext, width, heightText },
            guiTextBuf // sliderTitle
        );
        yNext += heightText;                

        this->zoomAmount = gui_sliderBar(
            (Rectangle){ x, yNext, width, heightSlider },
            this->zoomAmount,
            0.25,
            2.0 
        );
        yNext += padding + heightSlider;                


        // /**
        //  * render slider  
        //  */
        // sprintf(guiTextBuf, "playerSpeed: %.2f", state->playerSpeed);
        // gui_label(
        //     (Rectangle){ x, yNext, width, heightText },
        //     guiTextBuf // sliderTitle
        // );
        // yNext += heightText;                

        // state->playerSpeed = gui_sliderBar(
        //     (Rectangle){ x, yNext, width, heightSlider },
        //     state->playerSpeed,
        //     1.0,
        //     10.0
        // );
        // yNext += padding + heightSlider;                

        /**
         * render color picker
         */
        // Color c = RED;
        // gui_colorPicker(
        //     (Rectangle){ x, yNext, width, height },
        //     c
        // );
    }
};