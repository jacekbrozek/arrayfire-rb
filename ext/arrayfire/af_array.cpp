#include "af_array.h"

// Constructor

AfArray::AfArray(array afarray) {
  this->set_c_array(afarray);
}

AfArray::AfArray(af_array afarray) {
  this->set_c_array(afarray);
}

AfArray::AfArray(Array dimensions, Array elements, Symbol data_type) {
  af_array afarray = 0;
  dtype type = ruby_sym_to_dtype(data_type);

  dim4 tdims = ruby_array_to_dimensions(dimensions);

  switch (type) {
    case f32: create_internal_array<float>(afarray, elements, tdims, type); break;
    case c32: create_internal_array_complex<cfloat>(afarray, elements, tdims, type); break;
    case f64: create_internal_array<double>(afarray, elements, tdims, type); break;
    case c64: create_internal_array_complex<cdouble>(afarray, elements, tdims, type); break;
    case b8:  create_internal_array<char>(afarray, elements, tdims, type); break;
    case s32: create_internal_array<int>(afarray, elements, tdims, type); break;
    case u32: create_internal_array<uint>(afarray, elements, tdims, type); break;
    case s64: create_internal_array_long<intl>(afarray, elements, tdims, type); break;
    case u64: create_internal_array_long<uintl>(afarray, elements, tdims, type); break;
    case s16: create_internal_array_short<short>(afarray, elements, tdims, type); break;
    case u16: create_internal_array_ushort<ushort>(afarray, elements, tdims, type); break;
  }

  this->print();
}

// Public

void AfArray::print() {
  af_print(this->c_array);
}

AfArray* AfArray::multiply(Object other) {
  try {
    return AfArray::multiply_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::multiply_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::multiply_internal(AfArray other) {
  array afarray = this->c_array * other.get_c_array();
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_internal(int value) {
  array afarray = this->c_array * value;
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_assign(Object other) {
  try {
    return AfArray::multiply_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::multiply_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::multiply_assign_internal(AfArray other) {
  this->c_array *= other.get_c_array();
  this->print();
  return this;
}

AfArray* AfArray::multiply_assign_internal(int value) {
  this->c_array *= value;
  this->print();
  return this;
}

AfArray* AfArray::add(Object other) {
  try {
    return AfArray::add_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::add_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::add_internal(AfArray other) {
  array afarray = this->c_array + other.get_c_array();
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::add_internal(int value) {
  array afarray = this->c_array + value;
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::add_assign(Object other) {
  try {
    return AfArray::add_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::add_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::add_assign_internal(AfArray other) {
  this->c_array += other.get_c_array();
  this->print();
  return this;
}

AfArray* AfArray::add_assign_internal(int value) {
  this->c_array += value;
  this->print();
  return this;
}

AfArray* AfArray::div(Object other) {
  try {
    return AfArray::div_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::div_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::div_internal(AfArray other) {
  array afarray = this->c_array / other.get_c_array();
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::div_internal(int value) {
  array afarray = this->c_array / value;
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::div_assign(Object other) {
  try {
    return AfArray::div_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::div_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::div_assign_internal(AfArray other) {
  this->c_array /= other.get_c_array();
  this->print();
  return this;
}

AfArray* AfArray::div_assign_internal(int value) {
  this->c_array /= value;
  this->print();
  return this;
}

AfArray* AfArray::sub(Object other) {
  try {
    return AfArray::sub_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::sub_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::sub_internal(AfArray other) {
  array afarray = this->c_array - other.get_c_array();
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sub_internal(int value) {
  array afarray = this->c_array - value;
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sub_assign(Object other) {
  try {
    return AfArray::sub_assign_internal(from_ruby<AfArray>(other));
  } catch(...) {
    return AfArray::sub_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::sub_assign_internal(AfArray other) {
  this->c_array -= other.get_c_array();
  this->print();
  return this;
}

AfArray* AfArray::sub_assign_internal(int value) {
  this->c_array -= value;
  this->print();
  return this;
}

AfArray* AfArray::randu(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::randu(tdims, type);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::randn(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::randu(tdims, type);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::lower(bool is_unit_diag) {
  array afarray = af::lower(this->c_array, is_unit_diag);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::upper(bool is_unit_diag) {
  array afarray = af::upper(this->c_array, is_unit_diag);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::constant(Object value, Array dimensions, Symbol data_type) {
  array afarray = 0;
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  switch (type) {
    case f32: afarray = af::constant(cast_ruby_to<float>(value), tdims, type); break;
    case c32: afarray = af::constant(cast_ruby_to_complex<cfloat>(value), tdims, type); break;
    case f64: afarray = af::constant(cast_ruby_to<double>(value), tdims, type); break;
    case c64: afarray = af::constant(cast_ruby_to_complex<cdouble>(value), tdims, type); break;
    case b8:  afarray = af::constant(cast_ruby_to<char>(value), tdims, type); break;
    case s32: afarray = af::constant(cast_ruby_to<int>(value), tdims, type); break;
    case u32: afarray = af::constant(cast_ruby_to<uint>(value), tdims, type); break;
    case s64: afarray = af::constant(cast_ruby_to_long<intl>(value), tdims, type); break;
    case u64: afarray = af::constant(cast_ruby_to_long<uintl>(value), tdims, type); break;
    case s16: afarray = af::constant(cast_ruby_to_short<short>(value), tdims, type); break;
    case u16: afarray = af::constant(cast_ruby_to_ushort<ushort>(value), tdims, type); break;
  }
  af_print(afarray);

  return new AfArray(afarray);
}

AfArray* AfArray::range(int seq_dim, Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::range(tdims, seq_dim, type);
  af_print(afarray);

  return new AfArray(afarray);
}

AfArray* AfArray::cast(Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  af_array afarray;
  af_cast(&afarray, this->c_array.get(), type);
  af_print_array(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::as(Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  array afarray = this->c_array.as(type);
  af_print(afarray);
  return new AfArray(afarray);
}

// Primitive casting

template<typename T>
T AfArray::cast_ruby_to(Object ruby_object) {
  return from_ruby<T>(ruby_object);
}

template<typename T>
T AfArray::cast_ruby_to_short(Object ruby_object) {
  return NUM2SHORT(ruby_object);
}

template<typename T>
T AfArray::cast_ruby_to_ushort(Object ruby_object) {
  return NUM2USHORT(ruby_object);
}

template<typename T>
T AfArray::cast_ruby_to_long(Object ruby_object) {
  return FIX2LONG(ruby_object.value());
}

template<typename T>
T AfArray::cast_ruby_to_complex(Object ruby_object) {
  double real = from_ruby<double>(ruby_object.call("real"));
  double imaginary = from_ruby<double>(ruby_object.call("imaginary"));
  return T(real, imaginary);
}

// Array Casting

template<typename T>
T* AfArray::cast_ruby_array_to(Array elements) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    casted_elements[i] = from_ruby<T>(elements[i]);
  };
  return casted_elements;
}

template<typename T>
T* AfArray::cast_ruby_array_to_short(Array elements) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    casted_elements[i] = NUM2SHORT(elements[i].value());
  };
  return casted_elements;
}

template<typename T>
T* AfArray::cast_ruby_array_to_ushort(Array elements) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    casted_elements[i] = NUM2USHORT(elements[i].value());
  };
  return casted_elements;
}

template<typename T>
T* AfArray::cast_ruby_array_to_long(Array elements) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    casted_elements[i] = FIX2LONG(elements[i].value());
  };
  return casted_elements;
}

template<typename T>
T* AfArray::cast_ruby_array_to_complex(Array elements) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object ruby_object = Object(elements[i]);
    double real = from_ruby<double>(ruby_object.call("real"));
    double imaginary = from_ruby<double>(ruby_object.call("imaginary"));
    casted_elements[i] = T(real, imaginary);
  };
  return casted_elements;
}

void AfArray::set_seed(int seed) {
  setSeed(NUM2ULL(seed));
}

int AfArray::get_seed() {
  return ULL2NUM(getSeed());
}

AfArray* AfArray::row(int index) {
  array afarray = this->c_array.row(index);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::rows(int first, int last) {
  array afarray = this->c_array.rows(first, last);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::col(int index) {
  array afarray = this->c_array.col(index);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cols(int first, int last) {
  array afarray = this->c_array.cols(first, last);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::slice(int index) {
  array afarray = this->c_array.slice(index);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::slices(int first, int last) {
  array afarray = this->c_array.slices(first, last);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::lookup(Array idx) {
  af::array indices(idx.size(), ruby_array_to_ints(idx));
  array afarray = af::lookup(this->c_array, indices);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::real() {
  array afarray = af::real(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::imag() {
  array afarray = af::imag(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::conjg() {
  array afarray = af::conjg(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::diag(int num, bool extract) {
  array afarray = af::diag(this->c_array, num, extract);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::identity(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::identity(tdims, type);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::iota(Array dimensions, Array tile_dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  dim4 tile_dims = ruby_array_to_dimensions(tile_dimensions);
  array afarray = af::iota(tdims, tile_dims, type);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::is_nan() {
  array afarray = af::isNaN(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::is_inf() {
  array afarray = af::isInf(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::is_zero() {
  array afarray = af::iszero(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

size_t AfArray::allocated() {
  return this->c_array.allocated();
}

size_t AfArray::bytes() {
  return this->c_array.bytes();
}

AfArray* AfArray::copy() {
  array afarray = this->c_array.copy();
  af_print(afarray);
  return new AfArray(afarray);
}

Array AfArray::dims() {
  return dimensions_to_ruby_array(this->c_array.dims());
}

int AfArray::elements() {
  return this->c_array.elements();
}

int AfArray::numdims() {
  return this->c_array.numdims();
}

AfArray* AfArray::H() {
  array afarray = this->c_array.H();
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::transposed() {
  array afarray = this->c_array.T();
  af_print(afarray);
  return new AfArray(afarray);
}

Symbol AfArray::type() {
  return dtype_to_ruby_sym(this->c_array.type());
}

Object AfArray::scalar() {
  dtype type = this->c_array.type();
  switch (type) {
    case f32: return to_ruby<float>(this->c_array.scalar<float>()); break;
    case c32: return complex_to_ruby<cfloat>(this->c_array.scalar<cfloat>()); break;
    case f64: return to_ruby<double>(this->c_array.scalar<double>()); break;
    case c64: return complex_to_ruby<cdouble>(this->c_array.scalar<cdouble>()); break;
    case b8:  return to_ruby<char>(this->c_array.scalar<char>()); break;
    case s32: return to_ruby<int>(this->c_array.scalar<int>()); break;
    case u32: return to_ruby<uint>(this->c_array.scalar<uint>()); break;
    case s64: return LONG2NUM(this->c_array.scalar<intl>()); break;
    case u64: return ULL2NUM(this->c_array.scalar<uintl>()); break;
    case s16: return to_ruby<short>(this->c_array.scalar<short>()); break;
    case u16: return to_ruby<ushort>(this->c_array.scalar<ushort>()); break;
  }
}

bool AfArray::isbool() {
  return this->c_array.isbool();
}

bool AfArray::iscolumn() {
  return this->c_array.iscolumn();
}

bool AfArray::iscomplex() {
  return this->c_array.iscomplex();
}

bool AfArray::isdouble() {
  return this->c_array.isdouble();
}

bool AfArray::isempty() {
  return this->c_array.isempty();
}

bool AfArray::isfloating() {
  return this->c_array.isfloating();
}

bool AfArray::isinteger() {
  return this->c_array.isinteger();
}

bool AfArray::isreal() {
  return this->c_array.isreal();
}

bool AfArray::isrealfloating() {
  return this->c_array.isrealfloating();
}

bool AfArray::isrow() {
  return this->c_array.isrow();
}

bool AfArray::isscalar() {
  return this->c_array.isscalar();
}

bool AfArray::issingle() {
  return this->c_array.issingle();
}

bool AfArray::issparse() {
  return this->c_array.issparse();
}

bool AfArray::isvector() {
  return this->c_array.isvector();
}

AfArray* AfArray::flat() {
  array afarray = af::flat(this->c_array);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::flip(uint dimension) {
  array afarray = af::flip(this->c_array, dimension);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::join(int dimension, Array arrays) {
  af_array afarray;
  size_t count = arrays.size() + 1;
  af_array c_arrays[4];
  c_arrays[0] = this->c_array.get();
  for (size_t index = 1; index < count; index++) {
    c_arrays[index] = from_ruby<AfArray>(arrays[index-1].value()).c_array.get();
  }
  af_join_many(&afarray, dimension, count, c_arrays);
  af_print_array(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::moddims(Array dimensions) {
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::moddims(this->c_array, tdims);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::reorder(int x, int y, int z, int w) {
  array afarray = af::reorder(this->c_array, x, y, z, w);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::replace(AfArray conditions, Object replacement) {
  try {
    AfArray replacement_array = from_ruby<AfArray>(replacement);
    af::replace(this->c_array, conditions.get_c_array(), replacement_array.get_c_array());
    this->print();
    return this;
  } catch(...) {
    double replacement_value = from_ruby<double>(replacement);
    af::replace(this->c_array, conditions.get_c_array(), replacement_value);
    this->print();
    return this;
  }
}

AfArray* AfArray::select(AfArray conditions, Object otherwise) {
  try {
    AfArray otherwise_array = from_ruby<AfArray>(otherwise);
    array afarray = af::select(conditions.get_c_array(), this->c_array, otherwise_array.get_c_array());
    af_print(afarray);
    return new AfArray(afarray);
  } catch(...) {
    double otherwise_value = from_ruby<double>(otherwise);
    array afarray = af::select(conditions.get_c_array(), this->c_array, otherwise_value);
    af_print(afarray);
    return new AfArray(afarray);
  }
}

AfArray* AfArray::shift(int x, int y, int z, int w) {
  array afarray = af::shift(this->c_array, x, y, z, w);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::tile(int x, int y, int z, int w) {
  array afarray = af::tile(this->c_array, x, y, z, w);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::transpose(bool conjugate) {
  array afarray = af::transpose(this->c_array, conjugate);
  af_print(afarray);
  return new AfArray(afarray);
}

Array AfArray::lu() {
  array lower, upper, pivot;
  af::lu(lower, upper, pivot, this->c_array);
  af_print(lower);
  af_print(upper);
  af_print(pivot);
  Array result;
  result.push(new AfArray(lower));
  result.push(new AfArray(upper));
  result.push(new AfArray(pivot));
  return result;
}

Array AfArray::qr() {
  array q, r, tau;
  af::qr(q, r, tau, this->c_array);
  af_print(q);
  af_print(r);
  af_print(tau);
  Array result;
  result.push(new AfArray(q));
  result.push(new AfArray(r));
  result.push(new AfArray(tau));
  return result;
}

Array AfArray::svd() {
  array u, s, vt;
  af::svd(u, s, vt, this->c_array);
  af_print(u);
  af_print(s);
  af_print(vt);
  Array result;
  result.push(new AfArray(u));
  result.push(new AfArray(s));
  result.push(new AfArray(vt));
  return result;
}

Object AfArray::det() {
  dtype type = this->c_array.type();
  switch (type) {
    case f32: return to_ruby<float>(af::det<float>(this->c_array)); break;
    case c32: return complex_to_ruby<cfloat>(af::det<cfloat>(this->c_array)); break;
    case f64: return to_ruby<double>(af::det<double>(this->c_array)); break;
    case c64: return complex_to_ruby<cdouble>(af::det<cdouble>(this->c_array)); break;
    case b8:  return to_ruby<char>(af::det<char>(this->c_array)); break;
    case s32: return to_ruby<int>(af::det<int>(this->c_array)); break;
    case u32: return to_ruby<uint>(af::det<uint>(this->c_array)); break;
    case s64: return LONG2NUM(af::det<intl>(this->c_array)); break;
    case u64: return ULL2NUM(af::det<uintl>(this->c_array)); break;
    case s16: return to_ruby<short>(af::det<short>(this->c_array)); break;
    case u16: return to_ruby<ushort>(af::det<ushort>(this->c_array)); break;
  }
}

float AfArray::dot(AfArray other, Symbol opt_lhs, Symbol opt_rhs) {
  float result = af::dot<float>(this->c_array, other.get_c_array(), ruby_sym_to_opts(opt_lhs), ruby_sym_to_opts(opt_rhs));
  return result;
}

AfArray* AfArray::matmul(AfArray other, Symbol opt_lhs, Symbol opt_rhs) {
  array afarray = af::matmul(this->c_array, other.get_c_array(), ruby_sym_to_opts(opt_lhs), ruby_sym_to_opts(opt_rhs));
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::solve(AfArray other, Symbol opts) {
  array afarray = af::solve(this->c_array, other.get_c_array(), ruby_sym_to_opts(opts));
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::solveLU(AfArray a, AfArray pivot, AfArray b, Symbol opts) {
  array afarray = af::solveLU(a.get_c_array(), pivot.get_c_array(), b.get_c_array(), ruby_sym_to_opts(opts));
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cholesky(bool is_upper) {
  array afarray;
  int info = af::cholesky(afarray, this->c_array, is_upper);
  af_print(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::inverse(Symbol opts) {
  array afarray = af::inverse(this->c_array, ruby_sym_to_opts(opts));
  af_print(afarray);
  return new AfArray(afarray);
}

double AfArray::norm(double p, double q, Symbol norm_type) {
  double result = af::norm(this->c_array, ruby_sym_to_norm_type(norm_type), p, q);
  return result;
}

unsigned AfArray::rank(double tolerance) {
  unsigned result = af::rank(this->c_array, tolerance);
  return result;
}

// AfArray* AfArray::create_strided_array(Array elements, Array dimensions, int offset, Array strides, Symbol data_type, Symbol source) {
//   array afarray = 0;
//   dtype type = ruby_sym_to_dtype(data_type);
//   dim4 tdims = ruby_array_to_dimensions(dimensions);
//   dim4 tstrides = ruby_array_to_dimensions(strides);
//   switch (type) {
//     case f32: afarray = af::createStridedArray(cast_ruby_array_to<float>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case c32: afarray = af::createStridedArray(cast_ruby_array_to_complex<cfloat>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case f64: afarray = af::createStridedArray(cast_ruby_array_to<double>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case c64: afarray = af::createStridedArray(cast_ruby_array_to_complex<cdouble>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case b8:  afarray = af::createStridedArray(cast_ruby_array_to<char>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case s32: afarray = af::createStridedArray(cast_ruby_array_to<int>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case u32: afarray = af::createStridedArray(cast_ruby_array_to<uint>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case s64: afarray = af::createStridedArray(cast_ruby_array_to_long<intl>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case u64: afarray = af::createStridedArray(cast_ruby_array_to_long<uintl>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source) ); break;
//     case s16: afarray = af::createStridedArray(cast_ruby_array_to_short<short>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source)); break;
//     case u16: afarray = af::createStridedArray(cast_ruby_array_to_ushort<ushort>(elements), offset, tdims, tstrides, type, ruby_sym_to_source(source)); break;
//   }
//   af_print(afarray);

//   return new AfArray(afarray);
// }

// Private

template<typename T>
VALUE AfArray::complex_to_ruby(T complex) {
  return rb_Complex(to_ruby<double>(complex.real), to_ruby<double>(complex.imag));
}

array AfArray::get_c_array() {
  return this->c_array;
}

void AfArray::set_c_array(af_array afarray) {
  this->c_array = array(afarray);
}

void AfArray::set_c_array(const array& afarray) {
  this->c_array = afarray;
}

dim4 AfArray::ruby_array_to_dimensions(Array dimensions) {
  size_t count = dimensions.size();
  dim4 tdims = dim4(1, 1, 1, 1);
  for (size_t index = 0; index < count; index++) {
    tdims[index] = from_ruby<uint>(dimensions[index]);
  }
  return tdims;
}

Array AfArray::dimensions_to_ruby_array(dim4 dimensions) {
  size_t count = dimensions.ndims();
  Array rb_array = Array();
  for (size_t index = 0; index < count; index++) {
    rb_array[index] = to_ruby<uint>(dimensions[index]);
  }
  return rb_array;
}

int* AfArray::ruby_array_to_ints(Array rb_array) {
  size_t count = rb_array.size();
  int array[count];
  for (size_t index = 0; index < count; index++) {
    array[index] = from_ruby<int>(rb_array[index]);
  }
  return array;
}

template<typename T>
void AfArray::create_internal_array(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    casted_elements[i] = from_ruby<T>(elements[i]);
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_long(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    casted_elements[i] = FIX2LONG(element.value());
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_short(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    casted_elements[i] = NUM2SHORT(element.value());
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_ushort(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    casted_elements[i] = NUM2USHORT(element.value());
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_complex(af_array afarray, Array elements, dim4 tdims, dtype type) {
  size_t count = elements.size();
  T casted_elements[count];
  for(size_t i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    double real = from_ruby<double>(element.call("real"));
    double imaginary = from_ruby<double>(element.call("imaginary"));
    casted_elements[i] = T(real, imaginary);
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}
