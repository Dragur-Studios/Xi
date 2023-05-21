workspace "Xi"
    architecture "x64"

    configurations { "Debug",  "Release", "Distribution" }

    flags { "MultiProcessorCompile" }
    
    -- Core Game Engine

    include "engine/core"
    
    include "tools/editor"
    include "runtime/xi"


