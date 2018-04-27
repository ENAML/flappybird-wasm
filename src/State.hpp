/**
 * -----------------------------------------------------------------------------
 * State
 * -----------------------------------------------------------------------------
 */
#pragma once

#include <vector>

#include "common.hpp"

using namespace std;


/**
 * SEE: https://github.com/bsansouci/reprocessing-example/tree/livestream-flappybird 
 */

// constants
const float jumpForce = -500.;
const float speed = 175.;
const float pipeWidth = 50.;
const float halfGap = 70.; 
const float birdSize = 15.; // 20.; // bird radius
const float gravity = 1400.;
const float birdX = 50.;
const float defaultBirdY = 50.;
// const float pipeHeight = 350.; // TODO: UNUSED; REMOVE
const float floorY = 500.;


enum class RunningT {
    Running,
    Dead,
    Restart,
};



class GameState
{
public:
    float birdY = defaultBirdY;
    float birdVY = 0.;
    vector<Vec2f> pipes = {
        Vec2f(0), 
        Vec2f(0), 
        Vec2f(0), 
        Vec2f(0), 
    };


    float xOffset = 0;
    RunningT running = RunningT::Running;
    // image: imageT,
    // font: fontT,
    int score = 0;

    GameState()
    {
        printlog(0, "creating GameState");

        int pipeX = 500;
        int incr = 200;

        for (auto& pipe : this->pipes)
        {
            pipe.x = pipeX;
            pipe.y = 150;

            pipeX += incr;
            // printlog(0, "pipe<%f, %f>", pipe.x, pipe.y);
        }
    }


    virtual ~GameState()
    {
        printlog(0, "destroying GameState");
    }
};


class State
{
public:
    // config / debug
    bool canUpdate = true;
    bool guiVisible = false;
    bool debugDraw = false;

    // default is 1; the higher the number,
    // the slower the game (for debugging mostly)
    int ticksPerUpdate = 1; // 2;
    
    // timing-related stuff
    int tick = 0;
    float frameTime = 0;
    int fps = 0;

    // screen
    int screenWidth = SCREEN_W;
    int screenHeight = SCREEN_H;

    // input
    bool mousePressed = false;
    bool mouseDown = false;
    Vector2 mousePressedPos = rlVec2(0, 0);
    Vector2 mouseDragPos = rlVec2(0, 0);
    Vector2 mousePos = rlVec2(0, 0);

    GameState gameState = GameState();

    // constructor
    State()
    {
        printlog(0, "creating State");
    }

    // destructor
    virtual ~State()
    {
        printlog(0, "destroying State");
    }
};