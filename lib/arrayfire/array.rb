module ArrayFire
  class Array
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

    def each_region(width, height, &block)
      rows_num, cols_num = self.dims
      for i in 0...cols_num-(width-1) do
        for j in 0...rows_num-(height-1) do
          yield self.cols(i, i+(width-1)).rows(j, j+(height-1)), i, j
        end
      end
    end

    def each_tile(width, height, &block)
      rows_num, cols_num = self.dims
      h = rows_num / height
      w = cols_num / width

      for i in 0...h do
        for j in 0...w do
          yield self.cols((i * width), (i * width + width - 1)).rows((j * height), (j * height + height - 1)), i, j
        end
      end
    end
  end
end
