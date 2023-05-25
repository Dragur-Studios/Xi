workspace "Xi"
    architecture "x64"

    configurations { "Debug",  "Release", "Distribution" }

    flags { "MultiProcessorCompile" }
    
    -- Core Game Engine

    include "engine/Core"
    
    include "tools/Editor"
    include "tools/Project Launcher"

    include "runtime/xi"


