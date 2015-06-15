module Platforms
	class Flash < Platform


		def initialize
      $libbuildtool_params.install_dir = "#{Dir.pwd}/Flash/"

    end

		def permute!
			# @optionParser.permute!
		end


		def validate!
		end


	end

end
