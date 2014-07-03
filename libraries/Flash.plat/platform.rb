module Platforms
	class Flash < Platform


		def initialize
      $options.install_dir = "#{Dir.pwd}/Flash/"

    end

		def permute!
			# @optionParser.permute!
		end



	end

end