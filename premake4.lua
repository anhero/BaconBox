if not solution() then
solution "BaconBox"
end
configurations { "Debug", "Release" }

--Options
newoption {
	trigger = "target",
   	value       = "platform",
  	description = "Set the target platform.",
  	allowed = {
  				{"SDL", "SDL"},
				{"Flash", "Flash"}, 
				{"Qt", "Qt"}, 
				{"ios", "ios"}
			}
}

if not _OPTIONS["target"] then
   _OPTIONS["target"] = "SDL"
end

newoption {
	trigger = "lua",
  	description = "Build the lua interpreter version of BaconBox."
}

newoption {
	trigger = "swig",
	value="SWIG_PATH",
  	description = "Swig executable. Default to `which swig`."
}

if not _OPTIONS["swig"] then
   _OPTIONS["swig"] = "`which swig`"
end


newoption {
	trigger = "libraries",
	value="PATH_TO_LIBRARIES",
  	description = "Path to the include, lib and bin folder for the current target."
}
if not _OPTIONS["libraries"] then
   _OPTIONS["libraries"] = ""
end

local libraries = "./libraries/" .. _OPTIONS["libraries"]



project "BaconBox"
kind "StaticLib"
language "C++"
location "build"

if _OPTIONS["lua"] then
	os.mkdir("build")
	os.execute(_OPTIONS["swig"] .. 
		" -lua -c++  -module BaconBox -ignoremissing -DBB_OPENGL -DBB_LUA -I. -I" 
		..  libraries .. "/include -o build/BaconBoxLua.cpp BaconBox/Special/Swig/BaconBox.i")
end 

files {"./build/**.h", "./build/**.cpp","./BaconBox/**.h", "./BaconBox/**.cpp" }




if not (_OPTIONS["target"] == "Flash") then
	if os.get() == "windows" then
		excludes {"**/libc/**"}
	else
		excludes {"**/Windows/**"}
	end
end

links{"JsonBox"}
includedirs {".",  libraries .. "/include" }
defines {"SIGLY_DEFAULT_MT_POLICY=sigly::SingleThreaded"}

excludes {"**/TinyXML/**"}
excludes {"**/OpenAL/**"}


configuration "Flash"
	excludes {"**/OpenGL/**"}

configuration "lua"
		defines {"BB_LUA"}
		links{"lua"}
configuration "not lua"
	excludes {"**/Lua/**"}

configuration "not ios"
	excludes {"**/ios/**"}

configuration "not Qt"
	excludes {"**/Qt/**"}

configuration "SDL"
		defines {"BB_SDL"}
configuration "not SDL"
	excludes {"**/SDL/**"}




configuration "Flash"
		defines {"DBB_FLASH_PLATFORM"}
configuration "not Flash"
	excludes {"**/Flash/**"}

configuration "Debug"
		defines {"BB_DEBUG"}



if _ACTION  == "clean" then
	os.rmdir("build")
end