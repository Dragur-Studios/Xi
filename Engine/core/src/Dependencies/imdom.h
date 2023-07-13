#pragma once

#include "imgui/imgui.h"

struct ImRect {
    ImVec2 start;
    ImVec2 end;
};

struct ImColorState {

    const ImColorState& operator=(const ImColorState& other) {
        if (&other != this) {
            this->normal = other.normal;
            this->active = other.active;
            this->hover = other.hover;

        }
    }

    static ImColorState Default() {
        ImColorState def_state = {};
        
        def_state.normal = -1;
        def_state.active = -1;
        def_state.hover = -1;

        return def_state;
    }

    unsigned int normal = 0;
    unsigned int active = 0;
    unsigned int hover = 0;

};

enum class ImTextAlignment {
    None = -1,
    Top_Left,
    Top_Middle,
    Top_Right,
    Center_Right,
    Bottom_Right,
    Bottom_Middle,
    Bottom_Left,
    Center_Left,
    Center
};

enum class ImFlexDirection {
    None = -1,
    Row,
    Column
};