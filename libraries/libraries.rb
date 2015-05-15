puts ":: BaconBox libraries.rb ::"
puts "   Debug information."
puts "   Platform : #{$PLATFORM}"


if $PLATFORM != "Android"
build 'zlib.desc'
end
build 'libpng.desc' #if $libbuildtool_params.platform_name != "Flash"
build 'lua.desc'
build 'jsonbox.desc'

if $PLATFORM != "Android" and $PLATFORM != "Flash"
	build 'libogg.desc'
	build 'libvorbis.desc'
	build 'SDL2.desc'
	build 'SDL2_mixer.desc'

	# We are not using glew on Darwin.
	unless $PLATFORM == "Darwin"
		build 'glew.desc'
	end
end

build 'physicsfs.desc'
build 'rapidxml.desc'
build 'sigly.desc'

