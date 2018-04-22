
#include "common.hpp"

#include "State.hpp"
#include "Renderer.hpp"
#include "IO.hpp"
#include "gui.h"


/**
 * wrapper object for game
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
App game;


void game_update()
{
    //---------------------------------------------------------------------------
    // update time 
    //---------------------------------------------------------------------------
    game.state.tick += 1;
    game.state.frameTime = GetFrameTime();
    game.state.fps = (int)(1.0f / game.state.frameTime);
    // printlog(0, "fps: %d | frameTime %f", game.state.fps, game.state.frameTime);
    
    //---------------------------------------------------------------------------
    // handle input 
    //---------------------------------------------------------------------------
    {
        // update cursor data
        game.state.mousePos = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game.state.mousePressedPos = GetMousePosition();           
            // printlog(0, "[%i] mouse pressed", game.state.tick);
        }

        game.state.mouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

        if (game.state.mouseDown)
        {
            game.state.mouseDragPos = GetMousePosition();
        }

        // toggle debug menu(s)
        if (IsKeyPressed(KEY_G))
        {
            game.state.guiVisible = game.state.guiVisible ? false : true;
        }
    }
    // println("mousePos{x: %f, y: %f}", getMouseX, game.state.mousePos.y);


    //---------------------------------------------------------------------------
    // Update
    //---------------------------------------------------------------------------
    if (
        game.state.canUpdate &&
        (
            game.state.ticksPerUpdate == 1 ||
            game.state.tick % game.state.ticksPerUpdate == 0
        )
    ) {
        
    }


    //---------------------------------------------------------------------------
    // Draw
    //---------------------------------------------------------------------------
    game.renderer.render(
        &game.state
    );

    // if (game.state.tick % 200 == 1)
    // {
    //     println("[DEBUG : %5i] ", game.state.tick);
    //     println("    entities: %zu", game.entityManager.mEntities.size());
    //     println("     bullets: %zu", game.entityManager.mBullets.size());
    //     println("   particles: %zu", game.particleManager.mParticles.size());
    // }

    //---------------------------------------------------------------------------
    // finish game loop iteration
    //---------------------------------------------------------------------------
    game.state.tick++;
}



/**
 * -----------------------------------------------------------------------------
 * /////////////////////////// <<  MAIN  >> ////////////////////////////////////
 * -----------------------------------------------------------------------------
 */
int main(int argc, char **argv)
{
 	//------------------------------------------------------------------------------ 
	// TEST / DEBUG
	//------------------------------------------------------------------------------ 
    

 	//------------------------------------------------------------------------------ 
	// Initialization
	//------------------------------------------------------------------------------ 

    // loadConfig("resources/test.json");


    SetConfigFlags(
        // FLAG_SHOW_LOGO |
        FLAG_VSYNC_HINT |
        FLAG_MSAA_4X_HINT |
        // FLAG_FULLSCREEN_MODE |
        // FLAG_WINDOW_RESIZABLE |
        0
    );
	InitWindow(
        game.state.screenWidth * game.renderer.platformRenderScale,
        game.state.screenHeight * game.renderer.platformRenderScale,
        (void *)"FLAPPY"
    );

    game.renderer.init();

    /**
     * init game
     */
    // TODO

    //------------------------------------------------------------------------------ 
    // BEGIN Main game loop
    //------------------------------------------------------------------------------    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(game_update, 0, 1);
    #else
        SetTargetFPS(60);

        while (!WindowShouldClose()) // Detect window close button or ESC key
        {
            game_update();
        }
    #endif

	//------------------------------------------------------------------------------   
	// De-Initialization
	//------------------------------------------------------------------------------    

    // Close window and OpenGL context
	CloseWindow();        

	return 0;
}