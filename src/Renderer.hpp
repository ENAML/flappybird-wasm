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

// Draw a part of a texture (defined by a rectangle) with 'pro' parameters
// NOTE: origin is relative to destination rectangle size
// see: raylib's "DrawTexturePro()"
void my_drawTexture(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint)
{
    // Check if texture is valid
    if (texture.id > 0)
    {
        if (sourceRec.width < 0) sourceRec.x -= sourceRec.width;
        if (sourceRec.height < 0) sourceRec.y -= sourceRec.height;

        rlEnableTexture(texture.id);

        rlPushMatrix();
            rlTranslatef((float)destRec.x, (float)destRec.y, 0);
            rlRotatef(rotation, 0, 0, 1);
            rlTranslatef(-origin.x, -origin.y, 0);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer

                // Bottom-left corner for texture and quad
                rlTexCoord2f((float)sourceRec.x/texture.width, (float)sourceRec.y/texture.height);
                rlVertex2f(0.0f, 0.0f);

                // Bottom-right corner for texture and quad
                rlTexCoord2f((float)sourceRec.x/texture.width, (float)(sourceRec.y + sourceRec.height)/texture.height);
                rlVertex2f(0.0f, (float)destRec.height);

                // Top-right corner for texture and quad
                rlTexCoord2f((float)(sourceRec.x + sourceRec.width)/texture.width, (float)(sourceRec.y + sourceRec.height)/texture.height);
                rlVertex2f((float)destRec.width, (float)destRec.height);

                // Top-left corner for texture and quad
                rlTexCoord2f((float)(sourceRec.x + sourceRec.width)/texture.width, (float)sourceRec.y/texture.height);
                rlVertex2f((float)destRec.width, 0.0f);
            rlEnd();
        rlPopMatrix();

        rlDisableTexture();
    }
}


struct Textures
{
    Texture2D ship1;
    Texture2D ship2;
    Texture2D ship3;
    Texture2D ship4;
    Texture2D ship5;

    Texture2D bullet1;
    Texture2D bullet2;
    Texture2D bullet3;
    Texture2D bullet4;
    Texture2D bullet5;
    
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

        this->mTextures.ship1 = LoadTexture("resources/flappy_assets/sprites/bluebird-downflap.png");
        // this->mTextures.ship2 = LoadTexture("resources/customsprites/ship2.png");
        // this->mTextures.ship3 = LoadTexture("resources/customsprites/ship3.png");
        // this->mTextures.ship4 = LoadTexture("resources/customsprites/ship4.png");
        // this->mTextures.ship5 = LoadTexture("resources/customsprites/ship5.png");
        // this->mTextures.bullet1 = LoadTexture("resources/customsprites/bullet1.png");
        // this->mTextures.bullet2 = LoadTexture("resources/customsprites/bullet2.png");
        // this->mTextures.bullet3 = LoadTexture("resources/customsprites/bullet3.png");
        // this->mTextures.bullet4 = LoadTexture("resources/customsprites/bullet4.png");
        // this->mTextures.bullet5 = LoadTexture("resources/customsprites/bullet5.png");
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
         */ 
        static float rot = 0;

        Texture2D tex = this->mTextures.ship1;
        Rectangle srcRect = {0, 0, tex.width, tex.height};

        Vec2f position = Vec2f(100, 100) * zoomScale;
        Vec2f size = Vec2f(tex.width, tex.height) * zoomScale;
        my_drawTexture(
            tex,
            srcRect,
            rlRect(position, size),
            rlVec2(size / 2),
            rot++,
            WHITE
        );

        

        // // draws a dot at entity's "center" position
        // auto draw_center = [&](Entity *e, Color c)
        // {
        //     // DrawRectangle(
        //     //     (e->position.x - 1) * zoomScale,
        //     //     (e->position.y - 1) * zoomScale,
        //     //     2 * zoomScale,
        //     //     2 * zoomScale,
        //     //     c 
        //     // );
        //     draw_rect(e, Vec2f(2), c);
        // };

        // // draws entity's outline 
        // auto draw_outline = [&](Entity *e, Color c)
        // {
        //     Rectf r = e->getRect();
        //     r.position.x *= zoomScale;
        //     r.position.y *= zoomScale;
        //     r.size.width *= zoomScale;
        //     r.size.height *= zoomScale;

        //     DrawRectangleLines(
        //         r.position.x,
        //         r.position.y,
        //         r.size.width,
        //         r.size.height,
        //         c 
        //     );

        //     // float thicc = 2;
        //     // auto p0 = rlVec2(r.position.x, r.position.y);
        //     // auto p1 = rlVec2(r.position.x + r.size.width, r.position.y);
        //     // auto p2 = rlVec2(r.position.x, r.position.y + r.size.height);
        //     // auto p3 = rlVec2(r.position.x + r.size.width, r.position.y + r.size.height);

        //     // DrawLineEx(p0, p1, thicc, c);
        //     // DrawLineEx(p0, p2, thicc, c);
        //     // DrawLineEx(p1, p3, thicc, c);
        //     // DrawLineEx(p2, p3, thicc, c);
        // };

        // auto draw_tex = [&](Entity *e, Texture2D tex, Vec2f offset, Vec2f drawScale, float rotation, Color col)
        // {
        //     auto texSizeScaled = Vec2f(tex.width, tex.height) * drawScale * zoomScale;

        //     DrawTexturePro(
        //         tex,
        //         rlRect(0, 0, tex.width, tex.height),
        //         rlRect((e->position + offset) * zoomScale, texSizeScaled),
        //         rlVec2(texSizeScaled / 2.0), // centered
        //         rotation,
        //         col
        //     );
        // };

        // for (auto &p : bgMngr->mParticles) {
        //     const auto BRIGHTEN = 30;
        //     auto c = this->mBGColor; 
        //     c.r += BRIGHTEN;
        //     c.g += BRIGHTEN;
        //     c.b += BRIGHTEN;
        //     draw_rect(&p, p.size, c);
        // }

        // entMngr->mEntities.for_each([&](Entity **entity, int idx) {
        //     assert(*entity != NULL);
        //     assert((*entity)->isExpired == false);

        //     Entity *e = *entity;

        //     switch( e->kind )
        //     {
        //         //----------------------------------------------------------------------
        //         // render player 
        //         //----------------------------------------------------------------------
        //         case Entity::Kind::kPlayer:
        //             {
        //                 PlayerShip *player = (PlayerShip *)e;

        //                 Color col = PLAYER_COLOR;
        //                 if (state->debugDraw)
        //                     col.a *= DEBUG_OPACITY;

        //                 draw_tex(
        //                     player,
        //                     this->mTextures.ship1,
        //                     Vec2f(0, -3),
        //                     Vec2f(0.25),
        //                     180,
        //                     col
        //                 );

        //                 if (state->debugDraw)
        //                 {
        //                     draw_outline(player, WHITE);
        //                     draw_center(player, WHITE);
        //                 }

        //             }
        //             break;


        //         //----------------------------------------------------------------------
        //         // render enemy
        //         //----------------------------------------------------------------------
        //         case Entity::Kind::kEnemy:
        //             {
        //                 Enemy *en = (Enemy *)e;

        //                 auto col = ENEMY_COLOR;
        //                 if (state->debugDraw)
        //                     col.a *= DEBUG_OPACITY;

        //                 draw_tex(
        //                     en,
        //                     this->mTextures.ship4,
        //                     Vec2f(0,0),
        //                     Vec2f(0.25),
        //                     0,
        //                     col
        //                 );

        //                 if (state->debugDraw)
        //                 {
        //                     draw_outline(en, WHITE);
        //                     draw_center(en, WHITE);
        //                 }
        //             }
        //             break;


        //         //----------------------------------------------------------------------
        //         // render bullet
        //         //----------------------------------------------------------------------
        //         case Entity::Kind::kBullet:
        //             {
        //                 Bullet *b = (Bullet *)e;

        //                 float colAlpha = state->debugDraw ? DEBUG_OPACITY : 1;

        //                 if (b->sourceKind == Entity::Kind::kPlayer) {
        //                     draw_tex(
        //                         b,
        //                         this->mTextures.bullet5,
        //                         Vec2f(0,0),
        //                         Vec2f(0.15),
        //                         90 + Math::degrees(Math::atan2(b->velocity)),
        //                         Fade(PLAYER_BULLET_COLOR, colAlpha)
        //                     );
        //                 } else {
        //                     draw_tex(
        //                         b,
        //                         this->mTextures.bullet2,
        //                         Vec2f(0,0),
        //                         Vec2f(0.2),
        //                         0,
        //                         Fade(ENEMY_BULLET_COLOR, colAlpha)
        //                     );
        //                 }



        //                 if (state->debugDraw)
        //                 {
        //                     draw_outline(b, WHITE);
        //                     // draw_center(b, WHITE);
        //                 }

        //             }
        //             break;


        //         //----------------------------------------------------------------------
        //         // DEFAULT
        //         //----------------------------------------------------------------------
        //         default:
        //             {
        //                 println("ERROR: NO [RENDER] FN FOR THIS KIND");
        //             }
        //             break;

        //     }
        // });

        // for (auto &particle : ptclMngr->mParticles)
        // {
        //     // auto alpha = Math::min(100, particle.ticksRemaining) / 100;
        //     draw_rect(&particle, particle.size,  Fade(WHITE, particle.getLife() ) );
        // }


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