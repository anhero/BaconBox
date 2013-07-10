--helper functions

function removeFromTable(value, table)
	for k,v in pairs(table) do
		if value == v then
			table[k] = nil
		end
	end
end

--Solution
solution "BaconBox"

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
   	value       = "1",
  	description = "Build the lua interpreter version of BaconBox.",
}



local  platformExclusion = {"OpenGL", "SDL", "Flash", "Qt", "ios", "Windows", "libc", "SDL", "SDL", "JsonBox", "RapidXml", "TinyXML", "Lua"}

function setExclusionList()
	function removeFromExcluded(value)
		removeFromTable(value, platformExclusion)
	end

	if _OPTIONS["lua"] then
		removeFromExcluded("Lua") 
	end

	if not (_OPTIONS["target"] == "Flash") then
		removeFromExcluded("OpenGL") 
		if os.get() == "windows" then
			removeFromExcluded("Windows") 
		else 
			removeFromExcluded("libc") 
		end
	end

	removeFromExcluded(_OPTIONS["target"]) 

	removeFromExcluded("JsonBox") 
	removeFromExcluded("RapidXml") 

end



configurations { "Debug", "Release" }

project "BaconBox"
kind "StaticLib"
language "C++"

--include needed folder
setExclusionList()
files {"./BaconBox/**.h", "./BaconBox/**.cpp" }
for k,v in pairs(platformExclusion) do
	excludes  {"**/" .. v .. "/**"}
end