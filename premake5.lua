-- premake5.lua
workspace "Visualiser"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Visualiser"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Lumina/LuminaExternal.lua"

group "App"
   include "Visualiser/Visualiser.lua"
group ""