workspace "RenderingEngine"
    configurations 
    {
        "Debug",
        "Release"
    }

    architecture "x64"


project "RenderingEngine"
    kind "ConsoleApp"

    language "C++"
    
    targetdir ("Binaries/%{prj.name}-%{cfg.buildcfg}-%{cfg.architecture}")

    systemversion "8.1"

    files 
    {
        "Source/**.h",
        "Source/**.cpp",
        "Dependencies/glad/src/**"
    }

    includedirs
    {
        "Source/Engine/Shaders/Public",
        "Source/Engine",
        "Source/Engine/Core/Window/Public",
        "Dependencies/glad/include",
        "Dependencies/SDL2/include"
    }

    libdirs
    {
        "Dependencies/SDL2/lib/x64"
    }

    links
    {
        "SDL2test",
        "SDL2main",
        "SDL2"
    }

    filter {"configurations:Debug"}
        defines {"RE_DEBUG"}
        symbols "On"

    filter {"configurations:Release"}
        defines {"RE_RELEASE"}
        optimize "On"

    postbuildcommands
    {
        "{COPY} Dependencies/SDL2/lib/x64/SDL2.dll Binaries/%{prj.name}-%{cfg.buildcfg}-%{cfg.architecture}"
    }
    