workspace "Taro"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Taro/vendor/GLFW/include"
IncludeDir["Glad"] = "Taro/vendor/Glad/include"
IncludeDir["ImGui"] = "Taro/vendor/imgui"
IncludeDir["glm"] = "Taro/vendor/glm"

include "Taro/vendor/GLFW"
include "Taro/vendor/Glad"
include "Taro/vendor/imgui"

project "Taro"
    location "Taro"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "trpch.h"
    pchsource "Taro/src/trpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "TR_PLATFORM_WINDOWS",
            "TR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    staticruntime "off"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Taro/vendor/spdlog/include",
        "Taro/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Taro"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "TR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "On"