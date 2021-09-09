include("conanbuildinfo.premake.lua")

workspace("Shape-Drawer")
	conan_basic_setup()
	linkoptions { conan_exelinkflags }
	
	architecture "x86_64"
	language "C++"
	cppdialect "C++17"
	startproject "Drawer"

	targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
	
	configurations
	{
		"Debug",
		"Release"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines {"NDEBUG", "RELEASE"}
		runtime "Release"
		symbols "off"
		optimize "on"


	project "Drawer"
		kind "ConsoleApp"

		files { 
			"src/**.h", 
			"src/**.cpp"
		}
