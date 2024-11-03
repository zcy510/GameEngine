workspace "Taro"
    architecture "x64"
    startproject "Taro-Editor"

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
IncludeDir["entt"] = "Taro/vendor/entt/include"
IncludeDir["stb_image"] = "Taro/vendor/stb_image"
IncludeDir["assimp"] = "Taro/vendor/Assimp/include"
IncludeDir["yaml_cpp"] = "Taro/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Taro/vendor/ImGuizmo"
IncludeDir["Box2D"] = "Taro/vendor/Box2D/include"

include "Taro/vendor/GLFW"
include "Taro/vendor/Glad"
include "Taro/vendor/Box2D"
include "Taro/vendor/imgui"
include "Taro/vendor/yaml-cpp"


project "Taro"
    location "Taro"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "trpch.h"
    pchsource "Taro/src/trpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
        "%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "YAML_CPP_STATIC_DEFINE"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Box2D}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}",
        "%{IncludeDir.ImGuizmo}"
    }

    libdirs
	{
		"Taro/vendor/Assimp/lib/Release",
        "Taro/vendor/yaml-cpp/bin/Debug-windows-x86_64/yaml-cpp"
	}

    links
    {
        "GLFW",
        "Glad",
        "Box2D",
        "ImGui",
        "yaml-cpp",
        "assimp-vc143-mt.lib",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "files:Taro/vendor/ImGuizmo/**.cpp"
    flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "TR_PLATFORM_WINDOWS",
            "TR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Taro/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.entt}"
    }

    links
    {
        "Taro"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "TR_PLATFORM_WINDOWS",
            "YAML_CPP_STATIC_DEFINE"
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "on"

project "Taro-Editor"
    location "Taro-Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Taro/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.yaml_cpp}"
    }

    links
    {
        "Taro"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "TR_PLATFORM_WINDOWS",
            "YAML_CPP_STATIC_DEFINE"
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "on"