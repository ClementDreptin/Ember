project "EmberEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Ember/vendor/spdlog/include",
		"%{wks.location}/Ember/src",
		"%{wks.location}/Ember/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links { "Ember" }

	filter "system:windows"
		systemversion "latest"

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
