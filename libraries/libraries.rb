if $libbuildtool_params.platform_name != "Android"
build 'zlib.desc'
end
build 'libpng.desc' #if $libbuildtool_params.platform_name != "Flash"
build 'lua.desc'
build 'jsonbox.desc'

if $libbuildtool_params.platform_name != "Android" and $libbuildtool_params.platform_name != "Flash"
	build 'libogg.desc'
	build 'libvorbis.desc'
	build 'SDL2.desc'
	build 'SDL2_mixer.desc'
	build 'glew.desc'
end

build 'physicsfs.desc'
build 'rapidxml.desc'
build 'sigly.desc'

