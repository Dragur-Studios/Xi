project "core"
    kind "staticLib"

    language "c++"
    cppdialect "c++latest"
    
    location "."   

    configurations { "Debug",  "Release", "Distribution" }

    -- targetdir ("../../Build/Engine/")
    -- objdir ("../../Build/Engine/")

    targetdir ("../../Build/%{cfg.buildCfg}/Engine/")
    objdir ("../../Build/%{cfg.buildCfg}/Engine")

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.c"
    }

    includedirs {
        "src/",

        "../../dependencies/glad/",
        "../../dependencies/glfw/",
        "../../dependencies/glm/",
        "../../dependencies/imgui/",

    }
    
    libdirs {
        "../../dependencies/glfw/",
    }

    links {  
        "glfw3"
    }

    defines { }
    

    filter "system:windows"
        staticruntime "off"
        systemversion "latest"
     
        defines { }

    filter "configurations:Debug"
        defines {  }
        symbols "on"
        buildoptions "/MDd"

    filter "configurations:Release"
        defines { }
        optimize "on"
        symbols "off"
        buildoptions "/MD"

        
    filter "configurations:Distribution"
        defines {  "NDEBUG" }
        optimize "on"
        symbols "off"
        buildoptions "/MD"
    
