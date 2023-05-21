project "Editor"
    kind "sharedLib"

    language "c++"
    cppdialect "c++latest"
    
    location "."   

    configurations { "Debug",  "Release", "Distribution" }

    targetdir ("../../Build/%{cfg.buildCfg}/Runtime/")
    objdir ("../../Build/%{cfg.buildCfg}/Runtime/")

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.c"
    }

    includedirs {
        "src/",

        "../../engine/Core/src",

        "../../dependencies/glad/",
        "../../dependencies/glfw/",
        "../../dependencies/glm/",
        "../../dependencies/imgui/",



    }
    
    libdirs {
        "Engine/",

        "../../dependencies/glfw/",
    }

    links { 
        "Core",
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
    
