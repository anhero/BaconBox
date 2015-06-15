puts ":: BaconBox libraries.rb ::"
puts "   Debug information."
puts "   Platform : #{$PLATFORM}"

# First, platform indepenent dependencies
build 'lua.desc'
build 'jsonbox.desc'
build 'rapidxml.desc'
build 'sigly.desc'

# We will use the platform-dependent zlib on iOS and Android.
if $PLATFORM != "Android" and $PLATFORM != "IOS"
	build 'zlib.desc'
end

# Using the crossbridge-provided PhysicsFS.
if $PLATFORM != "Flash"
	build 'physicsfs.desc'
end

# libPNG is not used for Flash builds.
if $PLATFORM != "Flash"
	build 'libpng.desc' 
end

# Finally, mobile and Flash builds will not use those libraries.
if $PLATFORM != "Android" and $PLATFORM != "Flash" and $PLATFORM != "IOS"
	build 'libogg.desc'
	build 'libvorbis.desc'
	build 'SDL2.desc'
	build 'SDL2_mixer.desc'

	# Furthermore, we are not using glew on OSX.
	unless $PLATFORM == "Darwin"
		build 'glew.desc'
	end
end
