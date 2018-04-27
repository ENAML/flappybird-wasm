/**
 * -----------------------------------------------------------------------------
 * Renderer
 * -----------------------------------------------------------------------------
 */
#pragma once

#include "rlgl.h"

#include "common.hpp"
#include "State.hpp"
#include "Resource.hpp"
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
                float btm_left_x = (float)sourceRec.position.x/texture.width; 
                float btm_left_y = (float)sourceRec.position.y/texture.height;
                rlTexCoord2f(btm_left_x, btm_left_y);
                rlVertex2f(0.0f, 0.0f);

                // Bottom-right corner for texture and quad
                float btm_right_x = (float)sourceRec.position.x/texture.width; 
                float btm_right_y = (float)(sourceRec.position.y + sourceRec.size.height)/texture.height;
                rlTexCoord2f(btm_right_x, btm_right_y);
                rlVertex2f(0.0f, (float)destRec.size.height);

                // Top-right corner for texture and quad
                float top_right_x = (float)(sourceRec.position.x + sourceRec.size.width)/texture.width;
                float top_right_y = (float)(sourceRec.position.y + sourceRec.size.height)/texture.height;
                rlTexCoord2f(top_right_x, top_right_y);
                rlVertex2f((float)destRec.size.width, (float)destRec.size.height);

                // Top-left corner for texture and quad
                float top_left_x = (float)(sourceRec.position.x + sourceRec.size.width)/texture.width;
                float top_left_y = (float)sourceRec.position.y/texture.height;
                rlTexCoord2f(top_left_x, top_left_y);
                rlVertex2f((float)destRec.size.width, 0.0f);
            rlEnd();
        rlPopMatrix();

        rlDisableTexture();
    }
}


class Renderer
{
public:
    TextureMap texMap;

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
        this->texMap = Resource::loadTextures();
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

        static const float DEBUG_OPACITY = 0.3;

        // static const Color COLOR_BIRD = (Color){255, 255, 255, 255};
        static const Color COLOR_DEBUG = (Color){255, 0, 113, 255};

        static const std::string TEX_BIRD_0 = "bluebird-downflap";
        static const std::string TEX_PIPE = "pipe-green";

        float zoomScale = (1.0 / this->mCamera.zoom) * this->platformRenderScale;
        // float scale = 1.0;


        auto draw_rect = [&](Vec2f position, Vec2f size, Color c)
        {
            DrawRectangleLines(
                (position.x) * zoomScale,
                (position.y) * zoomScale,
                size.x * zoomScale,
                size.y * zoomScale,
                c 
            );
        };
        auto draw_rect_centered = [&](Vec2f position, Vec2f size, Color c)
        {
            DrawRectangleLines(
                (position.x - size.x/2) * zoomScale,
                (position.y - size.y/2) * zoomScale,
                size.x * zoomScale,
                size.y * zoomScale,
                c 
            );
        };
        auto draw_circle = [&](Vec2f position, float radius, Color c)
        {
            DrawCircleLines(
                position.x * zoomScale,
                position.y * zoomScale,
                radius * zoomScale,
                c
            );
        };


        /**
         * Render pipes 
         */
        for (auto& pipe : state->gameState.pipes)
        {
            auto& gameState = state->gameState;

            // get texture
            auto& texData = this->texMap.find(TEX_PIPE)->second;
            Vec2f size = texData.srcFrame.size;

            auto xPos = pipe.x - gameState.xOffset;

            auto topPos = Vec2f(xPos, pipe.y - halfGap - size.height);
            auto btmPos = Vec2f(xPos, pipe.y + halfGap);

            // top render data
            Rectf topDestRect(topPos * zoomScale, size * zoomScale);
            auto topSrcFrame = texData.srcFrame;  // NOTE: reverse tex y for top
            topSrcFrame.size.height *= -1; 

            // btm render data
            Rectf btmDestRect(btmPos * zoomScale, size * zoomScale);


            // draw top pipe
            my_drawTexture(
                texData.tex,
                topSrcFrame,
                topDestRect,
                Vec2f(0),
                0
            );
            
            // draw btm pipe
            my_drawTexture(
                texData.tex,
                texData.srcFrame,
                btmDestRect,
                Vec2f(0),
                0
            );


            // DEBUG: draw outlines
            auto pipeSize = Vec2f(
                pipeWidth, // actual width (hard-coded in state)
                size.height
            ); 
            draw_rect(
                topPos,
                pipeSize,
                COLOR_DEBUG 
            );
            draw_rect(
                btmPos,
                pipeSize,
                COLOR_DEBUG 
            );
        }

        /**
         * Render bird
         */
        {
            // draw texture
            auto& texData = this->texMap.find(TEX_BIRD_0)->second;

            Vec2f position = Vec2f(birdX, state->gameState.birdY) * zoomScale;
            Vec2f size = texData.srcFrame.size * zoomScale;
            Rectf destRect(position, size);
            
            Vec2f offset(size / 2);

            my_drawTexture(
                texData.tex,
                texData.srcFrame,
                destRect,
                offset,
                0
            );

            // DEBUG: draw shape
            draw_circle(
                Vec2f(birdX, state->gameState.birdY),
                birdSize,
                COLOR_DEBUG
            );
        }


        // /**
        //  * TEST TEX RENDER
        //  * ---------------
        //  */ 
        // {
        //     static float rot = 0;

        //     auto& texData = this->texMap.find(TEX_BIRD_0)->second;

        //     Vec2f position = Vec2f(200, 100) * zoomScale;
        //     Vec2f size = texData.srcFrame.size * zoomScale * 2;
        //     Rectf destRect(position, size);
            
        //     Vec2f offset(size / 2);
        //     my_drawTexture(
        //         texData.tex,
        //         texData.srcFrame,
        //         destRect,
        //         offset,
        //         rot
        //     );

        //     rot++;
        // }




        

        /**
         * end camera 2d render
         */
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