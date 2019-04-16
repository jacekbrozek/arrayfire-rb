module ArrayFire
	class	Array
		def self.iota(dimensions, tile_dimensions = [1], data_type)
			self.iota_c(dimensions, tile_dimensions, data_type)
		end
	end
end