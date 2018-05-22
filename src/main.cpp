/**
 * -----------------------------------------------------------------------------
 * main.cpp
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "common.hpp"

#include "State.hpp"
#include "Renderer.hpp"
#include "gui.h"

/**
 * TODO:
 * - move this someplace better
 * - cleanup code
 * 
 * see for explanation:
 * https://yal.cc/rectangle-circle-intersection-test/
 */
bool circleRectCollision(Vec2f circlePos, float circleRadius, Vec2f rectPos, Vec2f rectSize)
{
    float cx = circlePos.x;
    float cy = circlePos.y;
    float cr = circleRadius;
    float rx = rectPos.x;
    float ry = rectPos.y;
    float rw = rectSize.width;
    float rh = rectSize.height;

    float deltaX = cx - Math::max(rx, Math::min(cx, rx + rw));
    float DeltaY = cy - Math::max(ry, Math::min(cy, ry + rh));
    return (deltaX * deltaX + DeltaY * DeltaY) < (cr * cr);   
}


/**
 * wrapper object for app
 */
class App
{
    public:
    State state;
    Renderer renderer; 

    App()
    {
        printlog(0, "Creating App");
    }

    virtual ~App()
    {}
};

/**
 * Global app variable
 */
App app;


void game_update()
{
    /**
     * update time 
     * ------------
     */
    app.state.tick += 1;
    app.state.frameTime = GetFrameTime();
    // printlog(1, "%f", app.state.frameTime);
    if (app.state.frameTime != 0)
        app.state.fps = 1.0f / app.state.frameTime;
    // printlog(0, "fps: %d | frameTime %f", app.state.fps, app.state.frameTime);
    
    /**
     * handle input 
     * -------------
     */
    {
        app.state.mousePressed = (
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || // click down
            IsKeyPressed(KEY_SPACE) || // space bar down
            IsGestureDetected(GESTURE_TAP) || IsGestureDetected(GESTURE_DOUBLETAP) // touch down
        );
        app.state.mouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

        app.state.mousePos = GetMousePosition();
        
        if (app.state.mousePressed)
        {
            app.state.mousePressedPos = GetMousePosition();
            // printlog(0, "[%i] mouse pressed", app.state.tick);
        }

        if (app.state.mouseDown)
        {
            app.state.mouseDragPos = GetMousePosition();
        }

        // toggle debug menu(s)
        if (IsKeyPressed(KEY_G))
        {
            app.state.guiVisible = app.state.guiVisible ? false : true;
        }
    }


    /**
     * Update
     * ------
     */
    if (
        app.state.canUpdate &&
        (
            app.state.ticksPerUpdate == 1 ||
            app.state.tick % app.state.ticksPerUpdate == 0
        )
    ) {
        auto& state = app.state;
        auto& gameState = state.gameState;

        auto update_bird = [&]()
        {
            // add gravity to bird vel
            gameState.birdVY += gravity * DELTA_TIME;

            // update bird pos
            gameState.birdY += gameState.birdVY * DELTA_TIME;
            // clamp bird pos to floor/ceil
            gameState.birdY = Math::clamp(
                gameState.birdY,
                birdSize,
                floorY - birdSize
            );
        };

        switch (app.state.gameState.running)        
        {
            case RunningT::Running:
                {
                    /**
                     * update xOffset
                     */
                    gameState.xOffset += speed * DELTA_TIME;

                    /**
                     * update bird
                     */
                    // trigger jump
                    if (state.mousePressed)
                        gameState.birdVY = jumpForce;
                    // update bird pos/vel
                    update_bird();

                    /**
                     * update pipes
                     */
                    for (auto& pipe : gameState.pipes)
                    {
                        // pipe needs new position
                        if (pipe.x - gameState.xOffset + pipeWidth <= 0.0)
                        {
                            // get pipe with highest x pos
                            auto maxPipe = Vec2f();
                            for (auto& pipe : gameState.pipes)
                                if (pipe.x > maxPipe.x)
                                    maxPipe = pipe;
                            
                            // set pipe pos based on max x pos
                            pipe.x = maxPipe.x + rng::range(200, 300);
                            pipe.y = rng::range(
                                50 + halfGap,
                                floorY - 50 - halfGap
                            );
                            // printlog(1, "update pipe! <x: %f, y: %f>", pipe.x, pipe.y);
                        }
                    }

                    /**
                     * detect collisions
                     */
                    bool hitPipe = false;
                    for (auto& pipe : gameState.pipes)
                    {
                        auto birdPos = Vec2f(birdX, gameState.birdY);
                        auto birdRadius = birdSize;

                        auto xPos = pipe.x - gameState.xOffset;

                        auto topPipePos = Vec2f(xPos, 0);
                        auto topPipeSize = Vec2f(pipeWidth, pipe.y - halfGap);

                        auto btmPipePos = Vec2f(xPos, pipe.y + halfGap);
                        auto btmPipeSize = Vec2f(pipeWidth, floorY);

                        bool topPipeCollides = circleRectCollision(birdPos, birdRadius, topPipePos, topPipeSize);
                        if (topPipeCollides)
                        {
                            // printlog(1, "TOP PIPE COLLIDES");
                            hitPipe = true;
                            break;
                        }

                        bool btmPipeCollides = circleRectCollision(birdPos, birdRadius, btmPipePos, btmPipeSize);
                        if (btmPipeCollides)
                        {
                            // printlog(1, "BTM PIPE COLLIDES");
                            hitPipe = true;
                            break;
                        }
                    }

                    bool hitFloor = gameState.birdY >= floorY - birdSize;                   
                    // if (hitFloor)
                    //     printlog(1, "hit floor :(");

                    /**
                     * handle collisions
                     */
                    if (hitPipe || hitFloor)
                    {
                        gameState.running = RunningT::Dead;

                        if (hitPipe)
                            gameState.birdVY = jumpForce;
                    }
                    
                    /**
                     * update score
                     */
                    for (auto& pipe : gameState.pipes)
                    {
                        // ((x, _)) => birdX +. xOffset <= x && birdX +. xOffset +. speed *. deltaTime > x,
                        bool scored = (
                            birdX + gameState.xOffset <= pipe.x &&
                            birdX + gameState.xOffset + speed * DELTA_TIME > pipe.x
                        );
                        if (scored)
                        {
                            gameState.score += 1;
                            // printlog(0, "score!: %d", gameState.score);
                        }
                    }

                }
                break;
            case RunningT::Dead:
                {
                    update_bird();

                    // if bird is at floor, move to restart
                    if (gameState.birdY >= floorY - birdSize)
                        gameState.running = RunningT::Restart;
                }
                break;
            case RunningT::Restart:
                {
                    if (state.mousePressed)
                    {
                        state.gameState = GameState();
                    }
                }
                break;
        }
    }


    /**
     * Draw
     * ------
     */
    app.renderer.render(
        &app.state
    );

    // if (app.state.tick % 200 == 1)
    // {
    //     println("[DEBUG : %5i] ", app.state.tick);
    // }


    /**
     * finish app loop iteration
     * --------------------------
     */
    app.state.tick++;
}



/**
 * -----------------------------------------------------------------------------
 * /////////////////////////// <<  MAIN  >> ////////////////////////////////////
 * -----------------------------------------------------------------------------
 */
int main(int argc, char **argv)
{
    /**
     * TEST / DEBUG
     * ------------
     */
    // return 0;
    

    /**
     * Initialization
     * --------------
     */
    SetConfigFlags(
        // FLAG_SHOW_LOGO |
        FLAG_VSYNC_HINT |
        FLAG_MSAA_4X_HINT |
        // FLAG_FULLSCREEN_MODE |
        // FLAG_WINDOW_RESIZABLE |
        0
    );
	InitWindow(
        app.state.screenWidth * app.renderer.platformRenderScale,
        app.state.screenHeight * app.renderer.platformRenderScale,
        "FLAPPY"
    );

    app.renderer.init();

    /**
     * BEGIN Main app loop
     * --------------------
     */    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(game_update, 0, 1);
    #else
        SetTargetFPS(FPS);

        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            game_update();
        }
    #endif

    /**
     * De-Initialization
     * -----------------
     */
    // Close window and OpenGL context
	CloseWindow();        

	return 0;
}