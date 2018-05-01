/**
 * -----------------------------------------------------------------------------
 * renderer.cpp
 * -----------------------------------------------------------------------------
 */
#include <string>
#include <iostream>

#include "rlgl.h"
#include "gui.h"

#include "Renderer.hpp"

/**
 * global static vars
 */
static const float DEBUG_OPACITY = 0.3;

// static const Color COLOR_BIRD = (Color){255, 255, 255, 255};
static const Color COLOR_DEBUG = (Color){255, 0, 113, 255};

// TEXTURE KEYS
static const std::string TEX_BACKGROUND = "background-day";
static const std::string TEX_PIPE = "pipe-green";
static const std::string TEX_FLOOR = "base";
static const std::string TEX_BIRD_0 = "yellowbird-downflap";
static const std::string TEX_BIRD_1 = "yellowbird-midflap";
static const std::string TEX_BIRD_2 = "yellowbird-upflap";
static const std::string TEX_NUM_0 = "num-0";
static const std::string TEX_NUM_1 = "num-1";
static const std::string TEX_NUM_2 = "num-2";
static const std::string TEX_NUM_3 = "num-3";
static const std::string TEX_NUM_4 = "num-4";
static const std::string TEX_NUM_5 = "num-5";
static const std::string TEX_NUM_6 = "num-6";
static const std::string TEX_NUM_7 = "num-7";
static const std::string TEX_NUM_8 = "num-8";
static const std::string TEX_NUM_9 = "num-9";

const std::string& num_char_to_key(char i)
{
    assert(i >= '0');
    assert(i <= '9');

    switch (i)
    {
        case '0':
            return TEX_NUM_0;
        case '1':
            return TEX_NUM_1;
        case '2':
            return TEX_NUM_2;
        case '3':
            return TEX_NUM_3;
        case '4':
            return TEX_NUM_4;
        case '5':
            return TEX_NUM_5;
        case '6':
            return TEX_NUM_6;
        case '7':
            return TEX_NUM_7;
        case '8':
            return TEX_NUM_8;
        case '9':
            return TEX_NUM_9;
        default:
            return TEX_NUM_0;
    }
}


/**
 * Draw a part of a texture (defined by a rectangle) with 'pro' parameters
 * NOTE: origin is relative to destination rectangle size
 * see: raylib's "DrawTexturePro()"
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


/**
 * Renderer Implementation
 * -----------------------
 */
void Renderer::init()
{
    // load textures
    this->texMap = Resource::loadTextures();
}

void Renderer::render(State *state)
{
    // pre-render
    BeginDrawing();
    ClearBackground(this->mBGColor);

    // render entities
    this->renderEntities(state);
    
    // render gui
    if (state->guiVisible)
        this->renderGui(state);

    // post-render
    EndDrawing();            
}

void Renderer::renderEntities(State *state)
{


    // set camera zoom (this affects everything that is rendered)
    this->mCamera.zoom = this->zoomCamera ? this->zoomAmount : 1.0;
    Begin2dMode(this->mCamera);


    float zoomScale = (1.0 / this->mCamera.zoom) * this->platformRenderScale;
    // float scale = 1.0;


    auto& gameState = state->gameState;


    /**
     * helper fns
     * TODO:
     * - put these in renderer or someplace else
     */
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
        DrawCircle(
            position.x * zoomScale,
            position.y * zoomScale,
            radius * zoomScale,
            c
        );
    };


    /**
     * Render background
     */
    {
        auto &texData = this->texMap.find(TEX_BACKGROUND)->second;

        Vec2f size = texData.srcFrame.size;
        Vec2f position = Vec2f(
            fmod(-gameState.xOffset / 2, size.width),
            0
        );

        // printlog(1, "w: %d | x: %d", (int)size.width, (int)position.x);

        while (position.x < state->screenWidth)
        {
            my_drawTexture(
                texData.tex,
                texData.srcFrame,
                Rectf(position * zoomScale, size * zoomScale),
                Vec2f(0)
            );

            position.x += size.width;
        }
    }


    /**
     * Render pipes 
     */
    for (auto& pipe : gameState.pipes)
    {
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


        // // DEBUG: draw outlines
        // auto pipeSize = Vec2f(
        //     pipeWidth, // actual width (hard-coded in state)
        //     size.height
        // ); 
        // draw_rect(
        //     topPos,
        //     pipeSize,
        //     COLOR_DEBUG 
        // );
        // draw_rect(
        //     btmPos,
        //     pipeSize,
        //     COLOR_DEBUG 
        // );
    }

    /**
     * Render floor / ground
     */
    {
        auto &texData = this->texMap.find(TEX_FLOOR)->second;

        Vec2f size = texData.srcFrame.size;
        Vec2f position = Vec2f(
            fmod(-gameState.xOffset, size.width),
            floorY
        );

        // printlog(1, "w: %d | x: %d", (int)size.width, (int)position.x);

        while (position.x < state->screenWidth)
        {
            my_drawTexture(
                texData.tex,
                texData.srcFrame,
                Rectf(position * zoomScale, size * zoomScale),
                Vec2f(0)
            );

            position.x += size.width;
        }
    }

    /**
     * Render bird
     */
    {
        int frame = (int)(gameState.xOffset / 20) % 4;
        
        const string* texKey;
        switch (frame)
        {
            case 0:
                texKey = &TEX_BIRD_0;
                break;
            case 1:
                texKey = &TEX_BIRD_1;
                break;
            case 2:
                texKey = &TEX_BIRD_2;
                break;
            case 3:
                texKey = &TEX_BIRD_1;
                break;
            default:
                assert(false);
                break;
        }
        
        auto& texData = this->texMap.find(*texKey)->second;

        Vec2f position = Vec2f(birdX, gameState.birdY) * zoomScale;
        Vec2f size = texData.srcFrame.size * zoomScale;
        Rectf destRect(position, size);
        
        Vec2f offset(size / 2);

        // update bird rotation
        float newRotation = Math::map(
            gameState.birdVY,
            -500, 1100,
            -70, 75 // -67, 67
        );
        gameState.birdRotation = Math::lerp(0.3, gameState.birdRotation, newRotation);

        my_drawTexture(
            texData.tex,
            texData.srcFrame,
            destRect,
            offset,
            gameState.birdRotation 
        );

        // // DEBUG: draw shape
        // draw_circle(
        //     Vec2f(birdX, gameState.birdY),
        //     birdSize,
        //     COLOR_DEBUG
        // );
    }


    /**
     * Render score
     */
    {
        const int x_incr = 5; 

        // TODO:
        // use int division & modulo to get sprites instead of creating this spring
        auto score_str = std::to_string(gameState.score);

        int len = score_str.length();
        // TODO: for better results compute this per-digit (not all have same width)
        int sprite_width = this->texMap.find(TEX_NUM_0)->second.srcFrame.size.width; 
        int total_width = len*sprite_width + (len - 1)*x_incr; 
        int half_width = total_width / 2;
        int center_x = state->screenWidth / 2;
        int start_x = center_x - half_width;
        start_x -= 10; // quick fix for above TODO


        Vec2f position(start_x, 50);

        for (char c : score_str)
        {
            auto& numkey = num_char_to_key(c);
            auto& texData = this->texMap.find(numkey)->second;

            Vec2f size = texData.srcFrame.size;

            Rectf destRect(
                position * zoomScale,
                size * zoomScale
            );

            my_drawTexture(
                texData.tex,
                texData.srcFrame,
                destRect,
                Vec2f(0)
            );
            
            position.x += size.width + x_incr;

            // std::cout << c << ", ";
        }
        // std::cout << std::endl;
    }

    

    /**
     * end camera 2d render
     */
    End2dMode();
}



void Renderer::renderGui(State *state)
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