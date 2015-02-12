#if $options.platform_name != "Android"
libraries << 'zlib.desc'
#end
libraries << 'libpng.desc' #if $options.platform_name != "Flash"
libraries << 'lua.desc'
libraries << 'jsonbox.desc'

#if $options.platform_name != "Android" and $options.platform_name != "Flash"
	libraries << 'libogg.desc'
	libraries << 'libvorbis.desc'
	libraries << 'SDL2.desc'
	libraries << 'SDL2_mixer.desc'
	libraries << 'glew.desc'
#end

libraries << 'rapidxml.desc'
libraries << 'sigly.desc'
