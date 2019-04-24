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
    .define_singleton_method("constant", &AfArray::constant)
    .define_singleton_method("identity", &AfArray::identity)
    .define_singleton_method("iota_c", &AfArray::iota)
    .define_singleton_method("range", &AfArray::range)
    // .define_singleton_method("create_strided_array", &AfArray::create_strided_array)
    .define_method("print", &AfArray::print)
    .define_method("*", &AfArray::multiply)
    .define_method("/", &AfArray::div)
    .define_method("+", &AfArray::add)
    .define_method("-", &AfArray::sub)
    .define_method("row", &AfArray::row)
    .define_method("rows", &AfArray::rows)
    .define_method("col", &AfArray::col)
    .define_method("cols", &AfArray::cols)
    .define_method("slice", &AfArray::slice)
    .define_method("slices", &AfArray::slices)
    .define_method("lookup", &AfArray::lookup)
    .define_method("real", &AfArray::real)
    .define_method("imag", &AfArray::imag)
    .define_method("conjg", &AfArray::conjg)
    .define_method("*=", &AfArray::multiply_assign)
    .define_method("+=", &AfArray::add_assign)
    .define_method("/=", &AfArray::div_assign)
    .define_method("-=", &AfArray::sub_assign)
    .define_method("diag", &AfArray::diag, (Arg("num") = 0, Arg("extract") = true))
    .define_method("lower", &AfArray::lower, (Arg("is_unit_diag") = false))
    .define_method("upper", &AfArray::upper, (Arg("is_unit_diag") = false))
    .define_method("cast", &AfArray::cast)
    .define_method("as", &AfArray::as)
    .define_method("is_nan", &AfArray::is_nan)
    .define_method("is_inf", &AfArray::is_inf)
    .define_method("is_zero", &AfArray::is_zero)
    .define_method("allocated", &AfArray::allocated)
    .define_method("bytes", &AfArray::bytes)
    .define_method("copy", &AfArray::copy)
    .define_method("dims", &AfArray::dims)
    .define_method("elements", &AfArray::elements)
    .define_method("H", &AfArray::H)
    .define_method("T", &AfArray::transposed)
    .define_method("numdims", &AfArray::numdims)
    .define_method("type", &AfArray::type)
    .define_method("scalar", &AfArray::scalar)
    .define_method("bool?", &AfArray::isbool)
    .define_method("column?", &AfArray::iscolumn)
    .define_method("complex?", &AfArray::iscomplex)
    .define_method("double?", &AfArray::isdouble)
    .define_method("empty?", &AfArray::isempty)
    .define_method("floating?", &AfArray::isfloating)
    .define_method("integer?", &AfArray::isinteger)
    .define_method("real?", &AfArray::isreal)
    .define_method("real_floating?", &AfArray::isrealfloating)
    .define_method("row?", &AfArray::isrow)
    .define_method("scalar?", &AfArray::isscalar)
    .define_method("single?", &AfArray::issingle)
    .define_method("sparse?", &AfArray::issparse)
    .define_method("vector?", &AfArray::isvector)
    .define_method("flat", &AfArray::flat)
    .define_method("flip", &AfArray::flip)
    .define_method("join", &AfArray::join)
    .define_method("moddims", &AfArray::moddims)
    .define_method("reorder", &AfArray::reorder, (
      Arg("x"),
      Arg("y") = 1,
      Arg("z") = 2,
      Arg("w") = 3
    ))
    .define_method("replace", &AfArray::replace)
    .define_method("select", &AfArray::select)
    .define_method("shift", &AfArray::shift, (
      Arg("x"),
      Arg("y") = 0,
      Arg("z") = 0,
      Arg("w") = 0
    ))
    .define_method("tile", &AfArray::tile, (
      Arg("x"),
      Arg("y") = 1,
      Arg("z") = 1,
      Arg("w") = 1
    ))
    .define_method("transpose", &AfArray::transpose, (
      Arg("conjugate") = false
    ))
    .define_method("dot", &AfArray::dot, (
      Arg("other"),
      Arg("opt_lhs") = Symbol("mat_none"),
      Arg("opt_rhs") = Symbol("mat_none")
    ));
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

af::source ruby_sym_to_source(Symbol source) {
  std::map<Symbol, af::source> sources;
  sources.insert(std::make_pair("device", afDevice));
  sources.insert(std::make_pair("host", afHost));

  return sources.find(source)->second;
}

af::matProp ruby_sym_to_opts(Symbol option) {
  std::map<Symbol, af::matProp> options;
  options.insert(std::make_pair("mat_none", AF_MAT_NONE));
  options.insert(std::make_pair("mat_conj", AF_MAT_CONJ));

  return options.find(option)->second;
}

Symbol dtype_to_ruby_sym(dtype data_type) {
  std::map<dtype, Symbol> dtypes;
  dtypes.insert(std::make_pair(f32, "f32"));
  dtypes.insert(std::make_pair(c32, "c32"));
  dtypes.insert(std::make_pair(f64, "f64"));
  dtypes.insert(std::make_pair(c64, "c64"));
  dtypes.insert(std::make_pair( b8, "b8"));
  dtypes.insert(std::make_pair(s32, "s32"));
  dtypes.insert(std::make_pair(u32, "u32"));
  dtypes.insert(std::make_pair( u8, "u8"));
  dtypes.insert(std::make_pair(s64, "s64"));
  dtypes.insert(std::make_pair(u64, "u64"));
  dtypes.insert(std::make_pair(s16, "s16"));
  dtypes.insert(std::make_pair(u16, "u16"));

  return dtypes.find(data_type)->second;
}
