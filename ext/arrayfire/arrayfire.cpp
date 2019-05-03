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
    .define_singleton_method("solveLU", &AfArray::solveLU, (
      Arg("a"),
      Arg("pivot"),
      Arg("b"),
      Arg("opts") = Symbol("mat_none")
    ))
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
    ))
    .define_method("matmul", &AfArray::matmul, (
      Arg("other"),
      Arg("opt_lhs") = Symbol("mat_none"),
      Arg("opt_rhs") = Symbol("mat_none")
    ))
    .define_method("solve", &AfArray::solve, (
      Arg("other"),
      Arg("opts") = Symbol("mat_none")
    ))
    .define_method("cholesky", &AfArray::cholesky, (
      Arg("is_upper") = true
    ))
    .define_method("lu", &AfArray::lu)
    .define_method("qr", &AfArray::qr)
    .define_method("svd", &AfArray::svd)
    .define_method("det", &AfArray::det)
    .define_method("inverse", &AfArray::inverse, (
      Arg("opts") = Symbol("mat_none")
    ))
    .define_method("norm", &AfArray::norm, (
      Arg("p"),
      Arg("q"),
      Arg("norm_type") = Symbol("norm_euclid")
    ))
    .define_method("rank", &AfArray::rank, (
      Arg("tolerance") = 1E-5
    ))
    .define_method("cbrt", &AfArray::cbrt)
    .define_method("erf", &AfArray::erf)
    .define_method("erfc", &AfArray::erfc)
    .define_method("exp", &AfArray::exp)
    .define_method("expm1", &AfArray::expm1)
    .define_method("factorial", &AfArray::factorial)
    .define_method("lgamma", &AfArray::lgamma)
    .define_method("tgamma", &AfArray::tgamma)
    .define_method("log", &AfArray::log)
    .define_method("log10", &AfArray::log10)
    .define_method("log1p", &AfArray::log1p)
    .define_method("pow2", &AfArray::pow2)
    .define_method("**", &AfArray::pow)
    .define_method("root", &AfArray::root)
    .define_method("sqrt", &AfArray::sqrt)
    .define_method("acosh", &AfArray::acosh)
    .define_method("asinh", &AfArray::asinh)
    .define_method("atanh", &AfArray::atanh)
    .define_method("cosh", &AfArray::cosh)
    .define_method("sinh", &AfArray::sinh)
    .define_method("tanh", &AfArray::tanh)
    .define_method("&", &AfArray::bit_and)
    .define_method("|", &AfArray::bit_or)
    .define_method("^", &AfArray::bit_xor)
    .define_method("==", &AfArray::eq)
    .define_method("!=", &AfArray::neq)
    .define_method("and", &AfArray::logical_and)
    .define_method("or", &AfArray::logical_or)
    .define_method("-@", &AfArray::neg)
    .define_method("not", &AfArray::logical_not)
    .define_method(">", &AfArray::gt)
    .define_method("<", &AfArray::lt)
    .define_method(">=", &AfArray::ge)
    .define_method("<=", &AfArray::le)
    .define_method("abs", &AfArray::abs)
    .define_method("arg", &AfArray::arg)
    .define_method("ceil", &AfArray::ceil)
    .define_method("floor", &AfArray::floor)
    .define_method("hypot", &AfArray::hypot)
    .define_method("max", &AfArray::max)
    .define_method("min", &AfArray::min)
    .define_method("%", &AfArray::mod)
    .define_method("rem", &AfArray::rem)
    .define_method("round", &AfArray::round)
    .define_method("sign", &AfArray::sign)
    .define_method("trunc", &AfArray::trunc)
    .define_method("acos", &AfArray::acos)
    .define_method("asin", &AfArray::asin)
    .define_method("atan", &AfArray::atan)
    .define_method("atan2", &AfArray::atan2)
    .define_method("cos", &AfArray::cos)
    .define_method("sin", &AfArray::sin)
    .define_method("tan", &AfArray::tan);
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
  options.insert(std::make_pair("mat_lower", AF_MAT_LOWER));
  options.insert(std::make_pair("mat_upper", AF_MAT_UPPER));

  return options.find(option)->second;
}

af::normType ruby_sym_to_norm_type(Symbol norm_type) {
  std::map<Symbol, af::normType> options;
  options.insert(std::make_pair("norm_vector_1", AF_NORM_VECTOR_1));
  options.insert(std::make_pair("norm_vector_inf", AF_NORM_VECTOR_INF));
  options.insert(std::make_pair("norm_vector_2", AF_NORM_VECTOR_2));
  options.insert(std::make_pair("norm_vector_p", AF_NORM_VECTOR_P));
  options.insert(std::make_pair("norm_matrix_1", AF_NORM_MATRIX_1));
  options.insert(std::make_pair("norm_matrix_inf", AF_NORM_MATRIX_INF));
  options.insert(std::make_pair("norm_matrix_2", AF_NORM_MATRIX_2));
  options.insert(std::make_pair("norm_matrix_l_pq", AF_NORM_MATRIX_L_PQ));
  options.insert(std::make_pair("norm_euclid", AF_NORM_EUCLID));
  return options.find(norm_type)->second;
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
