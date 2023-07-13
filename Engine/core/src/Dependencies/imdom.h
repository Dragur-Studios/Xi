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

    unsigned int normal = 0;
    unsigned int active = 0;
    unsigned int hover = 0;

};
