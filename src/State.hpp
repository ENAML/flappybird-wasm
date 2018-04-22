/**
 * -----------------------------------------------------------------------------
 * State
 * -----------------------------------------------------------------------------
 */
#pragma once

#include <vector>

#include "common.hpp"

using namespace std;


/*
    SEE: https://github.com/bsansouci/reprocessing-example/tree/livestream-flappybird 

    // constants
    let jumpForce = (-500.);
    let speed = 175.;
    let pipeWidth = 50.;
    let halfGap = 70.;
    let birdSize = 20.;
    let gravity = 1400.;
    let birdX = 50.;
    let defaultBirdY = 50.;
    let pipeHeight = 350.;
    let floorY = 500.;

    type runningT =
    | Running
    | Dead
    | Restart;

    type stateT = {
    birdY: float,
    birdVY: float,
    pipes: list((float, float)),
    xOffset: float,
    running: runningT,
    image: imageT,
    font: fontT,
    score: int
    };


  {
    birdY: defaultBirdY,
    birdVY: 0.,
    pipes: [(200., 100.), (400., 100.), (600., 100.), (800., 100.)],
    xOffset: 0.,
    running: Running,
    image: Draw.loadImage(~filename="assets/flappy.png", ~isPixel=true, env),
    font: Draw.loadFont(~filename="assets/flappy.fnt", ~isPixel=true, env),
    score: 0
  }
 */


// constants
const float jumpForce = -500.;
const float speed = 175.;
const float pipeWidth = 50.;
const float halfGap = 70.;
const float birdSize = 20.;
const float gravity = 1400.;
const float birdX = 50.;
const float defaultBirdY = 50.;
const float pipeHeight = 350.;
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
    vector<Vec2f> pipes = { Vec2f(200., 100.), Vec2f(400., 100.), Vec2f(600., 100.), Vec2f(800., 100.) };
    float xOffset = 0;
    RunningT running = RunningT::Running;
    // image: imageT,
    // font: fontT,
    int score = 0;

    GameState()
    {
        printlog(0, "creating GameState");

        // for (auto& pipe : this->pipes)
        // {
        //     printlog(0, "pipe<%f, %f>", pipe.x, pipe.y);
        // }
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
    int mouseDown = 0;
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