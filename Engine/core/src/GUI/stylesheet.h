#pragma once

#include "imgui/imgui.h"

struct ImRect {
    ImVec2 start;
    ImVec2 end;
};

struct ImColorState {
    ImU32 normal = 0;
    ImU32 active = 0;
    ImU32 hover = 0;
};

enum TextAlignment {
    Top_Left,
    Top_Middle,
    Top_Right,
    Middle_Right,
    Bottom_Right,
    Bottom_Middle,
    Bottom_Left,
    Middle_Left,
    Middle
};

struct StyleSheet
{
    float width = 0;
    float height = 0;
    float rounding = 0;

    ImVec4 padding = { 0, 0, 0, 0 };
    ImVec4 margin = { 0, 0, 0, 0 };

    ImVec4 shadow = { 0, 0, 0, 0 };
    ImColorState shadow_color = { 0x11000000, 0x11000000,0x11000000 };

    ImVec4 border = { 0, 0, 0, 0 };
    ImColorState border_color = { 0xFF000000, 0xFF161616, 0xFF161616 };

    TextAlignment text_align = TextAlignment::Top_Left;
    ImColorState font_color = { 0xFFEEEEEE, 0xFFEEEEEE, 0xFFEEEEEE };
    ImColorState background_color = { 0xFF242424, 0xFF161616, 0xFF242424 };

};
