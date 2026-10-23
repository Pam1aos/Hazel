workspace "Hazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazel/vendor/ImGui"
IncludeDir["glm"] = "Hazel/vendor/glm"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/ImGui"

project "Hazel"
	location "Hazel"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect"C++17"
		systemversion "latest"

		defines{
			"HZ_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
			"_CRT_SECURE_NO_WARNINGS",
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING"
		}

		filter "configurations:Debug"
			defines { "HZ_DEBUG", "HZ_ENABLE_ASSERTS" }
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
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
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hazel",
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING"
		}

		filter "configurations:Debug"
			defines { "HZ_DEBUG", "HZ_ENABLE_ASSERTS" }
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			symbols "On"

		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			symbols "On"