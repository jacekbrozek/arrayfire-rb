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
  af_array c_array = 0;

  public:
  AfArray(array af_array) {
  	this->set_c_array(af_array);
		this->print();
  }

  AfArray(int rows, int cols, Array elements, Symbol data_type) {
    dtype type = ruby_sym_to_dtype(data_type);

    int count = elements.size();
    float trans_mat[count];
    for(int i = 0; i < count; i++) {
    	trans_mat[i] = from_ruby<float>(elements[i]);
	  };
     af::dim4 tdims(rows, cols, 1, 1);
     af_create_array(&this->c_array, trans_mat, tdims.ndims(), tdims.get(), type);
     this->print();
  }

  void print() {
    af_print_array(this->c_array);
  }

  AfArray multiply(AfArray other) {
  	afarray = this->c_array * other->get_c_array();
  	return new AfArray(afarray);
  }

  array get_c_array() {
  	return this->c_array;
  }

  void set_c_array(array afarray) {
  	this->c_array = afarray;
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
