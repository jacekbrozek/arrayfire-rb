#include "arrayfire_rb.h"
#include "af_array.h"

using namespace Rice;
using namespace af;

Module rb_mArrayFire;

extern "C" void Init_arrayfire() {
  rb_mArrayFire = define_module("ArrayFire")
    .define_singleton_method("info", &info);

  Class rb_cArray = define_class_under<AfArray>(rb_mArrayFire, "Array")
    .define_constructor(Constructor<AfArray, Array, Array, Symbol>())
    .define_singleton_method("randu", &AfArray::randu)
    .define_singleton_method("randn", &AfArray::randu)
    .define_singleton_method("get_seed", &AfArray::get_seed)
    .define_singleton_method("set_seed", &AfArray::set_seed)
    .define_method("print", &AfArray::print)
    .define_method("*", &AfArray::multiply)
    .define_method("/", &AfArray::div)
    .define_method("+", &AfArray::add);
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
