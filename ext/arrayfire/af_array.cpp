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

  this->head();
}

// Public

void AfArray::print() {
  af_print(this->c_array);
}

void AfArray::head() {
  if(this->dims()[0] > 5) {
    af_print(this->c_array(seq(0,4), span));
  } else {
    af_print(this->c_array);
  }
}

AfArray* AfArray::multiply(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::multiply_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::multiply_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::multiply_internal(AfArray other) {
  array afarray = this->c_array * other.get_c_array();
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_internal(int value) {
  array afarray = this->c_array * value;
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_assign(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::multiply_assign_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::multiply_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::multiply_assign_internal(AfArray other) {
  this->c_array *= other.get_c_array();
  this->head();
  return this;
}

AfArray* AfArray::multiply_assign_internal(int value) {
  this->c_array *= value;
  this->head();
  return this;
}

AfArray* AfArray::add(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::add_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::add_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::add_internal(AfArray other) {
  array afarray = this->c_array + other.get_c_array();
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::add_internal(int value) {
  array afarray = this->c_array + value;
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::add_assign(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::add_assign_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::add_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::add_assign_internal(AfArray other) {
  this->c_array += other.get_c_array();
  this->head();
  return this;
}

AfArray* AfArray::add_assign_internal(int value) {
  this->c_array += value;
  this->head();
  return this;
}

AfArray* AfArray::div(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::div_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::div_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::div_internal(AfArray other) {
  array afarray = this->c_array / other.get_c_array();
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::div_internal(int value) {
  array afarray = this->c_array / value;
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::div_assign(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::div_assign_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::div_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::div_assign_internal(AfArray other) {
  this->c_array /= other.get_c_array();
  this->head();
  return this;
}

AfArray* AfArray::div_assign_internal(int value) {
  this->c_array /= value;
  this->head();
  return this;
}

AfArray* AfArray::sub(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::sub_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::sub_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::sub_internal(AfArray other) {
  array afarray = this->c_array - other.get_c_array();
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sub_internal(int value) {
  array afarray = this->c_array - value;
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sub_assign(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::sub_assign_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::sub_assign_internal(from_ruby<int>(other));
  }
}

AfArray* AfArray::sub_assign_internal(AfArray other) {
  this->c_array -= other.get_c_array();
  this->head();
  return this;
}

AfArray* AfArray::sub_assign_internal(int value) {
  this->c_array -= value;
  this->head();
  return this;
}

AfArray* AfArray::randu(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::randu(tdims, type);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::randn(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::randu(tdims, type);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::lower(bool is_unit_diag) {
  array afarray = af::lower(this->c_array, is_unit_diag);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::upper(bool is_unit_diag) {
  array afarray = af::upper(this->c_array, is_unit_diag);
  af_head(afarray);
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
  af_head(afarray);

  return new AfArray(afarray);
}

AfArray* AfArray::range(int seq_dim, Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::range(tdims, seq_dim, type);
  af_head(afarray);

  return new AfArray(afarray);
}

AfArray* AfArray::cast(Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  af_array afarray;
  af_cast(&afarray, this->c_array.get(), type);
  // af_print_array(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::as(Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  array afarray = this->c_array.as(type);
  af_head(afarray);
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

void AfArray::set_device(int device) {
  af::setDevice(device);
}

void AfArray::set_backend(Symbol backend) {
  af::Backend bknd = ruby_sym_to_backend(backend);
  af::setBackend(bknd);
}

int AfArray::get_seed() {
  return ULL2NUM(getSeed());
}

AfArray* AfArray::row(int index) {
  array afarray = this->c_array.row(index);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::rows(int first, int last) {
  array afarray = this->c_array.rows(first, last);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::col(int index) {
  array afarray = this->c_array.col(index);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cols(int first, int last) {
  array afarray = this->c_array.cols(first, last);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::slice(int index) {
  array afarray = this->c_array.slice(index);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::slices(int first, int last) {
  array afarray = this->c_array.slices(first, last);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::lookup(Array idx) {
  af::array indices(idx.size(), ruby_array_to_ints(idx));
  array afarray = af::lookup(this->c_array, indices);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::real() {
  array afarray = af::real(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::imag() {
  array afarray = af::imag(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::conjg() {
  array afarray = af::conjg(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::diag(int num, bool extract) {
  array afarray = af::diag(this->c_array, num, extract);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::identity(Array dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::identity(tdims, type);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::iota(Array dimensions, Array tile_dimensions, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  dim4 tile_dims = ruby_array_to_dimensions(tile_dimensions);
  array afarray = af::iota(tdims, tile_dims, type);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::is_nan() {
  array afarray = af::isNaN(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::is_inf() {
  array afarray = af::isInf(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::is_zero() {
  array afarray = af::iszero(this->c_array);
  af_head(afarray);
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
  af_head(afarray);
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
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::transposed() {
  array afarray = this->c_array.T();
  af_head(afarray);
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
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::flip(uint dimension) {
  array afarray = af::flip(this->c_array, dimension);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::join(int dimension, AfArray other) {
  array afarray = af::join(dimension, this->c_array, other.get_c_array());
  // af_print_array(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::moddims(Array dimensions) {
  dim4 tdims = ruby_array_to_dimensions(dimensions);
  array afarray = af::moddims(this->c_array, tdims);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::reorder(int x, int y, int z, int w) {
  array afarray = af::reorder(this->c_array, x, y, z, w);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::replace(AfArray conditions, Object replacement) {
  if(replacement.is_a(Data_Type<AfArray>::klass())) {
    AfArray replacement_array = from_ruby<AfArray>(replacement);
    af::replace(this->c_array, conditions.get_c_array(), replacement_array.get_c_array());
    this->head();
    return this;
  } else {
    double replacement_value = from_ruby<double>(replacement);
    af::replace(this->c_array, conditions.get_c_array(), replacement_value);
    this->head();
    return this;
  }
}

AfArray* AfArray::select(AfArray conditions, Object otherwise) {
  if(otherwise.is_a(Data_Type<AfArray>::klass())) {
    AfArray otherwise_array = from_ruby<AfArray>(otherwise);
    array afarray = af::select(conditions.get_c_array(), this->c_array, otherwise_array.get_c_array());
    af_head(afarray);
    return new AfArray(afarray);
  } else {
    double otherwise_value = from_ruby<double>(otherwise);
    array afarray = af::select(conditions.get_c_array(), this->c_array, otherwise_value);
    af_head(afarray);
    return new AfArray(afarray);
  }
}

AfArray* AfArray::shift(int x, int y, int z, int w) {
  array afarray = af::shift(this->c_array, x, y, z, w);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::tile(int x, int y, int z, int w) {
  array afarray = af::tile(this->c_array, x, y, z, w);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::transpose(bool conjugate) {
  array afarray = af::transpose(this->c_array, conjugate);
  af_head(afarray);
  return new AfArray(afarray);
}

Array AfArray::lu() {
  array lower, upper, pivot;
  af::lu(lower, upper, pivot, this->c_array);
  // af_print(lower);
  // af_print(upper);
  // af_print(pivot);
  Array result;
  result.push(new AfArray(lower));
  result.push(new AfArray(upper));
  result.push(new AfArray(pivot));
  return result;
}

Array AfArray::qr() {
  array q, r, tau;
  af::qr(q, r, tau, this->c_array);
  // af_print(q);
  // af_print(r);
  // af_print(tau);
  Array result;
  result.push(new AfArray(q));
  result.push(new AfArray(r));
  result.push(new AfArray(tau));
  return result;
}

Array AfArray::svd() {
  array u, s, vt;
  af::svd(u, s, vt, this->c_array);
  // af_print(u);
  // af_print(s);
  // af_print(vt);
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
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::matmulTT(AfArray other) {
  array afarray = af::matmulTT(this->c_array, other.get_c_array());
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::solve(AfArray other, Symbol opts) {
  array afarray = af::solve(this->c_array, other.get_c_array(), ruby_sym_to_opts(opts));
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::solveLU(AfArray a, AfArray pivot, AfArray b, Symbol opts) {
  array afarray = af::solveLU(a.get_c_array(), pivot.get_c_array(), b.get_c_array(), ruby_sym_to_opts(opts));
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cholesky(bool is_upper) {
  array afarray;
  int info = af::cholesky(afarray, this->c_array, is_upper);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::inverse(Symbol opts) {
  array afarray = af::inverse(this->c_array, ruby_sym_to_opts(opts));
  af_head(afarray);
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

AfArray* AfArray::cbrt() {
  array afarray = af::cbrt(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::erf() {
  array afarray = af::erf(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::erfc() {
  array afarray = af::erfc(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::exp() {
  array afarray = af::exp(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::expm1() {
  array afarray = af::expm1(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::factorial() {
  array afarray = af::factorial(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::lgamma() {
  array afarray = af::lgamma(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::tgamma() {
  array afarray = af::tgamma(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::log() {
  array afarray = af::log(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::log10() {
  array afarray = af::log10(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::log1p() {
  array afarray = af::log1p(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::pow2() {
  array afarray = af::pow2(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::pow(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::pow_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::pow_internal(from_ruby<double>(other));
  }
}

AfArray* AfArray::pow_internal(AfArray other) {
  array afarray = af::pow(this->c_array, other.get_c_array());
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::pow_internal(double value) {
  array afarray = af::pow(this->c_array, value);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::root(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    return AfArray::root_internal(from_ruby<AfArray>(other));
  } else {
    return AfArray::root_internal(from_ruby<double>(other));
  }
}

AfArray* AfArray::root_internal(AfArray other) {
  array afarray = af::root(this->c_array, other.get_c_array());
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::root_internal(double value) {
  array afarray = af::root(this->c_array, value);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sqrt() {
  array afarray = af::sqrt(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::acosh() {
  array afarray = af::acosh(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::asinh() {
  array afarray = af::asinh(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::atanh() {
  array afarray = af::atanh(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cosh() {
  array afarray = af::cosh(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sinh() {
  array afarray = af::sinh(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::tanh() {
  array afarray = af::tanh(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::bit_and(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array & from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  } else {
    array afarray = this->c_array & from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  }
}

AfArray* AfArray::bit_or(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array | from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  } else {
    array afarray = this->c_array | from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  }
}

AfArray* AfArray::bit_xor(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array ^ from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  } else {
    array afarray = this->c_array ^ from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  }
}

AfArray* AfArray::eq(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array == from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };


  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array == from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array == from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array == cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("TrueClass") || other.class_of().name() == String("FalseClass")) {
    array afarray = this->c_array == from_ruby<bool>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::neq(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array != from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };


  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array != from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array != from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array != cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("TrueClass") || other.class_of().name() == String("FalseClass")) {
    array afarray = this->c_array != from_ruby<bool>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::logical_and(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array && from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };


  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array && from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array && from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array && cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("TrueClass") || other.class_of().name() == String("FalseClass")) {
    array afarray = this->c_array && from_ruby<bool>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::logical_or(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array || from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };


  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array || from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array || from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array || cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("TrueClass") || other.class_of().name() == String("FalseClass")) {
    array afarray = this->c_array || from_ruby<bool>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::neg() {
  array afarray = -this->c_array;
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::logical_not() {
  array afarray = !this->c_array;
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::gt(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array > from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };


  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array > from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array > from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array > cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::lt(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array < from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array < from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array < from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array < cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::ge(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array >= from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };


  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array >= from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array >= from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array >= cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::le(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array <= from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array <= from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array <= from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Complex")) {
    array afarray = this->c_array <= cast_ruby_to_complex<cdouble>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::abs() {
  array afarray = af::abs(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::arg() {
  array afarray = af::arg(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::ceil() {
  if(this->iscomplex()) {
    this->head();
    return new AfArray(this->c_array);
  };

  array afarray = af::ceil(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::floor() {
  if(this->iscomplex()) {
    this->head();
    return new AfArray(this->c_array);
  };

  array afarray = af::floor(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::hypot(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    if(this->iscomplex() || from_ruby<AfArray>(other).iscomplex()) {
      this->head();
      return new AfArray(this->c_array);
    };
    array afarray = af::hypot(this->c_array, from_ruby<AfArray>(other).get_c_array());
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = af::hypot(this->c_array, from_ruby<double>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::max(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = af::max(this->c_array, from_ruby<AfArray>(other).get_c_array());
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = af::max(this->c_array, from_ruby<double>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  // af_print(this->c_array);
  return new AfArray(this->c_array);
}

AfArray* AfArray::min(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = af::min(this->c_array, from_ruby<AfArray>(other).get_c_array());
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = af::min(this->c_array, from_ruby<double>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  // af_print(this->c_array);
  return new AfArray(this->c_array);
}

AfArray* AfArray::mod(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = this->c_array % from_ruby<AfArray>(other).get_c_array();
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Integer")) {
    array afarray = this->c_array % from_ruby<int>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = this->c_array % from_ruby<double>(other);
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::rem(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = af::rem(this->c_array, from_ruby<AfArray>(other).get_c_array());
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Integer")) {
    array afarray = af::rem(this->c_array, from_ruby<int>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = af::rem(this->c_array, from_ruby<double>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::round() {
  if(this->iscomplex()) {
    this->head();
    return new AfArray(this->c_array);
  };

  array afarray = af::round(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sign() {
  if(this->iscomplex()) {
    this->head();
    return new AfArray(this->c_array);
  };

  array afarray = af::sign(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::trunc() {
  if(this->iscomplex()) {
    this->head();
    return new AfArray(this->c_array);
  };

  array afarray = af::trunc(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::acos() {
  array afarray = af::acos(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::asin() {
  array afarray = af::asin(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::atan() {
  array afarray = af::atan(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::cos() {
  array afarray = af::cos(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::sin() {
  array afarray = af::sin(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::tan() {
  array afarray = af::tan(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::atan2(Object other) {
  if(other.is_a(Data_Type<AfArray>::klass())) {
    array afarray = af::atan2(this->c_array, from_ruby<AfArray>(other).get_c_array());
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Integer")) {
    array afarray = af::atan2(this->c_array, from_ruby<int>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  if(other.class_of().name() == String("Float")) {
    array afarray = af::atan2(this->c_array, from_ruby<double>(other));
    af_head(afarray);
    return new AfArray(afarray);
  };

  AfArray* afarray = AfArray::constant(to_ruby<int>(0), this->dims(), Symbol("b8"));
  // af_print(afarray->c_array);
  return afarray;
}

AfArray* AfArray::convolve(AfArray signal, AfArray filter, Symbol conv_mode, Symbol conv_domain) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  convDomain domain = ruby_sym_to_conv_domain(conv_domain);
  array afarray = af::convolve(signal.get_c_array(), filter.get_c_array(), mode, domain);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::convolve1(AfArray signal, AfArray filter, Symbol conv_mode, Symbol conv_domain) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  convDomain domain = ruby_sym_to_conv_domain(conv_domain);
  array afarray = af::convolve1(signal.get_c_array(), filter.get_c_array(), mode, domain);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::convolve2(AfArray signal, AfArray filter, Symbol conv_mode, Symbol conv_domain) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  convDomain domain = ruby_sym_to_conv_domain(conv_domain);
  array afarray = af::convolve2(signal.get_c_array(), filter.get_c_array(), mode, domain);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::convolve3(AfArray signal, AfArray filter, Symbol conv_mode, Symbol conv_domain) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  convDomain domain = ruby_sym_to_conv_domain(conv_domain);
  array afarray = af::convolve3(signal.get_c_array(), filter.get_c_array(), mode, domain);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::fft_convolve(AfArray signal, AfArray filter, Symbol conv_mode) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  array afarray = af::fftConvolve(signal.get_c_array(), filter.get_c_array(), mode);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::fft_convolve2(AfArray signal, AfArray filter, Symbol conv_mode) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  array afarray = af::fftConvolve2(signal.get_c_array(), filter.get_c_array(), mode);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::fft_convolve3(AfArray signal, AfArray filter, Symbol conv_mode) {
  convMode mode = ruby_sym_to_conv_mode(conv_mode);
  array afarray = af::fftConvolve2(signal.get_c_array(), filter.get_c_array(), mode);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::dft_plain() {
  array afarray = af::dft(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::dft_dims(Array dims) {
  dim4 tdims = ruby_array_to_dimensions(dims);
  array afarray = af::dft(this->c_array, tdims);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::dft_norm_dims(double norm_factor, Array dims) {
  dim4 tdims = ruby_array_to_dimensions(dims);
  array afarray = af::dft(this->c_array, norm_factor, tdims);
  af_head(afarray);
  return new AfArray(afarray);
}

Array AfArray::setup_mnist_internal(int perc, std::string path) {
  array train_images, test_images;
  array train_target, test_target;
  int num_classes, num_train, num_test;
  // Load mnist data
  float frac = (float)(perc) / 100.0;
  setup_mnist<true>(&num_classes, &num_train, &num_test,
                   train_images, test_images, train_target, test_target, frac, path);

  Array result;
  result.push(new AfArray(train_images));
  result.push(new AfArray(test_images));
  result.push(new AfArray(train_target));
  result.push(new AfArray(test_target));
  result.push(num_classes);
  result.push(num_train);
  result.push(num_test);
  return result;
}

void AfArray::mnist_display_results(AfArray test_images, AfArray test_output, AfArray test_actual, int num_display) {
  display_results<true>(test_images.get_c_array(), test_output.get_c_array(), test_actual.get_c_array(), num_display);
}

AfArray* AfArray::sigmoid() {
  array afarray = af::sigmoid(this->c_array);
  af_head(afarray);
  return new AfArray(afarray);
}

AfArray* AfArray::take(Object s0, Object s1, Object s2, Object s3) {
  af::index idx0 = parse_index(s0);
  af::index idx1 = parse_index(s1);
  af::index idx2 = parse_index(s2);
  af::index idx3 = parse_index(s3);
  array afarray = this->c_array(idx0, idx1, idx2, idx3);
  af_head(afarray);
  return new AfArray(afarray);
}

float AfArray::sum() {
  return af::sum<float>(this->c_array);
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
  // af_head(afarray);

//   return new AfArray(afarray);
// }

// Private

void AfArray::af_head(array afarray) {
  printf("%s\n", "Showing head");
  if(afarray.dims(0) > 5) {
    if(afarray.dims(1) > 10) {
      af_print(afarray(seq(0,4), seq(0,9)));
    } else {
      af_print(afarray(seq(0,4), span));
    }
  } else {
    if(afarray.dims(1) > 10) {
      af_print(afarray(span, seq(0,9)));
    } else {
      af_print(afarray);
    }
  }
}

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

af::index AfArray::parse_index(Object ruby_index) {
  if(ruby_index.is_a(Data_Type<AfArray>::klass())) {
    return af::index(from_ruby<AfArray>(ruby_index).get_c_array());
  };

  if(ruby_index.class_of().name() == String("Integer")) {
    return af::index(from_ruby<int>(ruby_index));
  };

  if(ruby_index.class_of().name() == String("Symbol")) {
    if(Symbol(ruby_index).str() == "span") {
      return af::index(span);
    };
    if(Symbol(ruby_index).str() == "end") {
      return af::index(end);
    };
  };

  if(ruby_index.class_of().name() == String("Seq")) {
    double begin = from_ruby<double>(ruby_index.iv_get(Identifier("@first")));
    double end = from_ruby<double>(ruby_index.iv_get(Identifier("@last")));
    double step = from_ruby<double>(ruby_index.iv_get(Identifier("@step")));
    return af::index(af::seq(begin, end, step));
  }
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
