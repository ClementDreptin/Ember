workspace "Ember"
	architecture "x64"

	configurations {"Debug", "Release", "Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Ember/vendor/GLFW/include"
IncludeDir["glad"] = "Ember/vendor/glad/include"
IncludeDir["imgui"] = "Ember/vendor/imgui"
IncludeDir["glm"] = "Ember/vendor/glm"
IncludeDir["stb_image"] = "Ember/vendor/stb_image"

include "Ember/vendor/GLFW"
include "Ember/vendor/glad"
include "Ember/vendor/imgui"

project "Ember"
	location "Ember"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ebpch.h"
	pchsource "Ember/src/ebpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links {
		"GLFW",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {"EB_PLATFORM_WINDOWS", "EB_BUILD_DLL", "GLFW_INCLUDE_NONE"}

	filter "configurations:Debug"
		defines "EB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EB_DIST"
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

	files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

	includedirs {
		"Ember/vendor/spdlog/include",
		"Ember/src",
		"Ember/vendor",
		"%{IncludeDir.glm}"
	}

	links {"Ember"}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {"EB_PLATFORM_WINDOWS"}

	filter "configurations:Debug"
		defines "EB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EB_DIST"
		runtime "Release"
		optimize "on"


project "EmberEditor"
	location "EmberEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

	includedirs {
		"Ember/vendor/spdlog/include",
		"Ember/src",
		"Ember/vendor",
		"%{IncludeDir.glm}"
	}

	links {"Ember"}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {"EB_PLATFORM_WINDOWS"}

	filter "configurations:Debug"
		defines "EB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EB_DIST"
		runtime "Release"
		optimize "on"