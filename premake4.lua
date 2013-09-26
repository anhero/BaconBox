if not solution() then
solution "BaconBox"
end




local config = {}

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
	if not _OPTIONS["crossbridge"] then
   		_OPTIONS["target"] = "SDL"
	else 
		_OPTIONS["target"] = "Flash"
	end
end



newoption {
	trigger = "lua",
  	description = "Build the lua interpreter version of BaconBox."
}


newoption {
	trigger = "swig",
	value="SWIG_PATH",
  	description = "Swig executable. Default to 'swig'."
}

if not _OPTIONS["swig"] then
   _OPTIONS["swig"] = "swig"
end


newoption {
	trigger = "crossbridge",
	value="CROSSBRIDGE_PATH",
  	description = "Path to the crossbridge SDK folder."
}

newoption {
	trigger = "flex",
	value="FLEX_PATH",
  	description = "Path to the flex SDK folder."
}

newoption {
	trigger = "noProjectSetup",
  	description = "This flag prevent the project setup, generating swig binding for example."
}


newoption {
	trigger = "libraries",
	value="LIBRARIES_PAIR",
  	description = "Architecture and platform pair. For FreeBSD i686 you would write --target=FreeBSD/i686. It must correspond to the name of your platform/architecture folder in the libraries folder."
}

if not _OPTIONS["libraries"] then
   _OPTIONS["libraries"] = ""
end

config.target = _OPTIONS["target"]
config.lua = _OPTIONS["lua"]
config.swig =  _OPTIONS["swig"]
config.setupProject = not _OPTIONS["noProjectSetup"]
config.crossbridgePath =  _OPTIONS["crossbridge"]
config.flexPath = _OPTIONS["flex"]
config.librariesPath = "./libraries/" .. _OPTIONS["libraries"]
config.OS = os.get()
config.defines = {}
config.excludes = {}
config.links = {}
config.includedirs = {}
config.linkoptions = {}
config.buildoptions  = {}
config.libdirs   = {}

config.addLibdirs = function (libdir)
	table.insert(config.libdirs, libdir)
end
config.addBuildoptions = function (buildoption)
	table.insert(config.buildoptions, buildoption)
end
config.addLinkoptions = function (linkoption)
	table.insert(config.linkoptions, linkoption)
end
config.addIncludeDir = function (includeDir)
	table.insert(config.includedirs, includeDir)
end
config.addLinks = function (link)
	table.insert(config.links, link)
end
config.addExclude = function (exclude)
	table.insert(config.excludes, exclude)
end
config.addDefine = function (define)
	table.insert(config.defines, define)
end

config.getDefineList = function ()
	local defineList = ""
	for k,v in pairs(config.defines) do
		defineList =  defineList .. "-D" .. v .. " "
	end
	return defineList
end

config.getIncludeDirList = function ()
	local includeDirList = ""
	for k,v in pairs(config.includedirs) do
		includeDirList =  includeDirList .. "-I" .. v .. " "
	end
	return includeDirList
end

project "BaconBox"

if config.target == "Flash" then
	kind "ConsoleApp"
else
	kind "StaticLib"
end

language "C++"
location "build"

if _ACTION  == "clean" then
	os.rmdir("build")
	os.remove("EntityWrapper.swc")
	os.remove("BaconBox/Special/Flash/BaconBox/EntityWrapper/EntityHolderMovieClip.abc")
else

os.mkdir("build")

config.addLinks "JsonBox" 

config.addIncludeDir(".")
config.addIncludeDir(config.librariesPath .. "/include")

config.addDefine("SIGLY_DEFAULT_MT_POLICY=sigly::SingleThreaded")

config.addExclude "**/TinyXML/**"
config.addExclude "**/OpenAL/**"


if config.lua then
	config.addDefine "BB_LUA"
else
	config.addExclude "**/Lua/**"
end


if config.target == "SDL" then
	if config.OS == "windows" then
		config.addExclude "**/libc/**"
	else
		config.addExclude "**/Windows/**" 
	end
	config.addDefine "BB_SDL"

else
	config.addExclude "**/SDL/**"
end

if config.target == "Flash" then
	config.addExclude "**/OpenGL/**"

	config.addExclude "**/TextRenderer.cpp" --TODO: REMOVE THIS HACK
	config.addExclude "**/BatchedVertexArray.cpp" --TODO: REMOVE THIS HACK
	config.addExclude "**/FlashExporterXmlReader.cpp" --TODO: REMOVE THIS HACK

	config.addDefine "BB_FLASH_PLATFORM"
	if config.setupProject then

		os.execute("java -jar " .. config.crossbridgePath .."/usr/lib/asc2.jar -merge -md -abcfuture -AS3 -import " ..  config.crossbridgePath .. "/usr/lib/builtin.abc -import " ..  config.crossbridgePath .. "/usr/lib/playerglobal.abc ./BaconBox/Special/Flash/BaconBox/EntityWrapper/EntityHolderTextField.as ./BaconBox/Special/Flash/BaconBox/EntityWrapper/EntityHolderMovieClip.as")
		os.execute(config.flexPath .."/bin/compc -compiler.source-path ./BaconBox/Special/Flash -include-classes BaconBox.EntityWrapper.EntityHolderTextField BaconBox.EntityWrapper.EntityHolderMovieClip -output ./EntityWrapper.swc")
		os.execute("cp " .. config.crossbridgePath .. "/usr/share/LSOBackingStore.as ./build")
		os.execute("java -jar " .. config.crossbridgePath .."/usr/lib/asc2.jar -merge -md " .. 
					"-import " .. config.crossbridgePath .. "/usr/lib/builtin.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/playerglobal.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/BinaryData.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/ISpecialFile.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/IBackingStore.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/IVFS.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/InMemoryBackingStore.abc " ..
					"-import " .. config.crossbridgePath .. "/usr/lib/PlayerKernel.abc " ..
					"./BaconBox/Special/Flash/URLLoaderVFS.as ./build/LSOBackingStore.as -outdir ./build -out VFS")
		if config.lua then
			os.execute(config.crossbridgePath .. "/usr/bin/swig -as3 -c++ -module BaconBox -ignoremissing " .. config.getDefineList() ..  "-package BaconBox " .. config.getIncludeDirList() .. "-o ./build/BaconBoxAS3.cpp BaconBox/Special/Flash/BaconBoxAS3.i")
			os.execute("java -jar " .. config.crossbridgePath .."/usr/lib/asc2.jar -merge -md -abcfuture -AS3 -import " ..  config.crossbridgePath .. "/usr/lib/builtin.abc -import " ..  config.crossbridgePath .. "/usr/lib/playerglobal.abc ./build/BaconBox.as")
		else
			print("FLASH WITHOUT LUA ISN'T IMPLEMENTED YET!!!")
		end
	end
	config.addLinkoptions "VFS.abc"
	config.addLinkoptions "BaconBox.abc"
	config.addLinkoptions "-lAS3++"
	config.addLinkoptions "-emit-swc=BaconBox"

	config.addLinks "png" 
	config.addLinks "z" 

	if config.lua then
	config.addLinks "lua" 
	end


	config.addBuildoptions "-emit-swf"

	targetname "BaconBox"
	targetextension ".swc"
	targetprefix ""
else
	config.addExclude "**/Flash/**"
end

if config.target == "ios" then

else
	config.addExclude "**/ios/**"
end

if config.target == "Qt" then

else
	config.addExclude "**/Qt/**"
end

if config.lua and config.setupProject then
	os.execute(_OPTIONS["swig"] .. 
		" -lua -c++  -module BaconBox -ignoremissing " .. config.getDefineList() .. config.getIncludeDirList() ..
		" -o build/BaconBoxLua.cpp BaconBox/Special/Swig/BaconBox.i")

end


config.addLibdirs(config.librariesPath .. "/lib")




files {"./BaconBox/**.h", "./BaconBox/**.cpp","./build/**.h", "./build/**.cpp"}

defines(config.defines)
excludes(config.excludes)
links(config.links)
includedirs(config.includedirs)
linkoptions(config.linkoptions)
buildoptions(config.buildoptions)
libdirs(config.libdirs)

configuration "Debug"
		defines {"BB_DEBUG"}

end