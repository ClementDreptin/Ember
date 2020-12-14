include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Ember"
	architecture "x86_64"
	startproject "EmberEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Ember/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Ember/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Ember/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Ember/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Ember/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Ember/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Ember/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Ember/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Ember/vendor/GLFW"
	include "Ember/vendor/Glad"
	include "Ember/vendor/imgui"
	include "Ember/vendor/yaml-cpp"
group ""

include "Ember"
include "Sandbox"
include "EmberEditor"
