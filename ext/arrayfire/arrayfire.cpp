#include "arrayfire_rb.h"
#include "test.h"

using namespace Rice;
using namespace af;

Module rb_mArrayFire;

void rb_frandu(int rows, int cols, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  array A = randu(rows, cols, type);
  af_print(A);
}

void rb_finfo() {
  info();
}

class AfArray {
  private:
  af_array c_array;

  public:
  AfArray(int rows, int cols, Array elements, Symbol data_type) {
    dtype type = ruby_sym_to_dtype(data_type);

    dim_t ndims = (dim_t)NUM2LONG(rows);
    dim_t* dimensions = (dim_t*)malloc(ndims * sizeof(dim_t));
    dim_t count = 1;
    for (size_t index = 0; index < ndims; index++) {
      dimensions[index] = (dim_t)NUM2LONG(RARRAY_AREF(cols, index));
      count *= dimensions[index];
    }

    float* host_array = (float*)malloc(count * sizeof(float));
    for (size_t index = 0; index < count; index++) {
      host_array[index] = (float)NUM2DBL(RARRAY_AREF(elements, index));
    }


    af_create_array(&c_array, host_array, ndims, dimensions, f32);
  }

  void print() {
    af_print_array(c_array);
  }
};

extern "C" void Init_arrayfire() {
  rb_mArrayFire = define_module("ArrayFire");

  Class rb_cArray = define_class_under<AfArray>(rb_mArrayFire, "Array")
    .define_constructor(Constructor<AfArray, int, int, Array, Symbol>())
    .define_method("print", &AfArray::print);
}

dtype ruby_sym_to_dtype(Symbol data_type) {
  std::map<Symbol, dtype> dtypes;
  dtypes.insert(std::make_pair("f32", f32));
  dtypes.insert(std::make_pair("c32", c32));
  dtypes.insert(std::make_pair("f64", f64));
  dtypes.insert(std::make_pair("c64", c64));
  dtypes.insert(std::make_pair("b8",  b8));
  dtypes.insert(std::make_pair("s32", s32));
  dtypes.insert(std::make_pair("u32", u32));
  dtypes.insert(std::make_pair("u8",  u8));
  dtypes.insert(std::make_pair("s64", s64));
  dtypes.insert(std::make_pair("u64", u64));
  dtypes.insert(std::make_pair("s16", s16));
  dtypes.insert(std::make_pair("u16", u16));

  return dtypes.find(data_type)->second;
}
