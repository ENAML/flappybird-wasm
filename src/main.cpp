/**
 * -----------------------------------------------------------------------------
 * main.cpp
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "common.hpp"

#include "State.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Renderer.hpp"

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
    Input::update(app.state);


    /**
     * update game
     * ------------
     */
    if (
        app.state.canUpdate &&
        (
            app.state.ticksPerUpdate == 1 ||
            app.state.tick % app.state.ticksPerUpdate == 0
        )
    ) {
        Game::update(app.state);
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