#include "raylib.h"


/**
    use `#pragma GCC diagnostic ignored "-W<option>"` to ignore compiler warnings.
    
    see:
    - https://codeyarns.com/2014/03/11/how-to-selectively-ignore-a-gcc-warning/
 */
// -------------------------------------------------------------
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

#define RAYGUI_STYLE_DEFAULT_DARK
#define RAYGUI_NO_STYLE_SAVE_LOAD       // Avoid compiling style load/save code
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#pragma GCC diagnostic pop
// -------------------------------------------------------------


void gui_sayHello()
{
    printf("hello, world [gui.c]\n");
}

void gui_label(Rectangle r, char *text)
{
    GuiLabel(r, text);
}

bool gui_toggleButton(Rectangle r, char *text, bool value)
{
    return GuiToggleButton(r, text, value);
}

int gui_measureText(char *text)
{
    return MeasureText(text, DEFAULT_TEXT_SIZE);
}

float gui_sliderBar(Rectangle bounds, float value, float minValue, float maxValue)
{
    return GuiSliderBar(bounds, value, minValue, maxValue);
}

Color gui_colorPicker(Rectangle bounds, Color color)
{
    return GuiColorPicker(bounds, color);
}