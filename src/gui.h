#pragma once

/**
 * -----------------------------------------------------------------------------
 * GUI
 * - RayGui doesn't seem to build properly with C++ so this and `gui.c` are
 * here to provide wrappers for RayGui functions which we can call from
 * anywhere else.
 * -----------------------------------------------------------------------------
 */

#include "raylib.h"

#ifdef __cplusplus
extern "C"
{
#endif



// C header here
void gui_sayHello(); // test fn
void gui_label(Rectangle r, char *text);
bool gui_toggleButton(Rectangle r, char *text, bool value);
int gui_measureText(char *text);
float gui_sliderBar(Rectangle bounds, float value, float minValue, float maxValue);
Color gui_colorPicker(Rectangle bounds, Color color);



#ifdef __cplusplus
}
#endif