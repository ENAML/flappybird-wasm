/**
 * -----------------------------------------------------------------------------
 * Game.hpp
 * -----------------------------------------------------------------------------
 */
#include "Game.hpp"


/**
 * TODO:
 * - move this someplace better
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



void Game::update(State& state)
{
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

    switch (state.gameState.running)        
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
                if (state.inputState.mousePressed)
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
                if (state.inputState.mousePressed)
                {
                    state.gameState = GameState();
                }
            }
            break;
    }
};