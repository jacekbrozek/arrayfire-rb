module ArrayFire
	class	Array
		def self.iota(dimensions, tile_dimensions = [1], data_type)
			self.iota_c(dimensions, tile_dimensions, data_type)
		end

    def dft(arg0 = nil, arg1 = nil)
      if arg0.is_a?(Float) && arg1.is_a?(::Array)
        return self.dft_norm_dims(arg0, arg1)
      end

      if arg0.is_a?(::Array)
        return self.dft_dims(arg0)
      end

      self.dft_plain
    end

    def coerce(other)
      [self.class.constant(other, self.dims, self.type), self]
    end
	end
end
