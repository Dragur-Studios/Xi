project "Xi"
    kind "consoleApp"

    language "c++"
    cppdialect "c++latest"
    
    location "."   

    configurations { "Debug",  "Release", "Distribution" }

    targetdir ("../../Build/%{cfg.buildCfg}/")
    objdir ("../../Build/%{cfg.buildCfg}/")

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.c"
    }

    includedirs {
        "src/",

        "../../engine/Core/src",

    }
    
    libdirs {
        "Engine/",
    }

    links { 
        "Core",    
     }

    defines {
        "ENGINE"
    }
    

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
    
