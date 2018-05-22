/**
 * -----------------------------------------------------------------------------
 * Input.cpp
 * -----------------------------------------------------------------------------
 */
#include "Input.hpp"

void Input::update(State &state)
{
    auto& inputState = state.inputState;

    inputState.mousePressed = (
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || // click down
        IsKeyPressed(KEY_SPACE) || // space bar down
        IsGestureDetected(GESTURE_TAP) || IsGestureDetected(GESTURE_DOUBLETAP) // touch down
    );
    inputState.mouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    auto pos = GetMousePosition();
    inputState.mousePos = Vec2f(pos.x, pos.y);
    
    if (inputState.mousePressed)
        inputState.mousePressedPos = inputState.mousePos;

    if (inputState.mouseDown)
        inputState.mouseDragPos = inputState.mousePos;
    
    state.inputState.toggleGui = IsKeyPressed(KEY_G);
};