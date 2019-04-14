#include "af_array.h"

// AfArray::AfArray(af_array afarray) {
//   this->set_c_array(afarray);
// }

AfArray::AfArray(array afarray) {
  this->set_c_array(afarray);
}

AfArray::AfArray(int rows, int cols, Array elements, Symbol data_type) {
  af_array afarray = 0;
  dtype type = ruby_sym_to_dtype(data_type);

  dim4 tdims(rows, cols, 1, 1);

  switch (type) {
    case f32: create_internal_array<float>(afarray, elements, tdims, type); break;
    case c32: create_internal_array_complex<cfloat>(afarray, elements, tdims, type); break;
    case f64: create_internal_array<double>(afarray, elements, tdims, type); break;
    case c64: create_internal_array_complex<cdouble>(afarray, elements, tdims, type); break;
    case b8:  create_internal_array<char>(afarray, elements, tdims, type); break;
    case s32: create_internal_array<int>(afarray, elements, tdims, type); break;
    case u32: create_internal_array<uint>(afarray, elements, tdims, type); break;
    case u8:  create_internal_array<uchar>(afarray, elements, tdims, type); break;
    case s64: create_internal_array<intl>(afarray, elements, tdims, type); break;
    case u64: create_internal_array<uintl>(afarray, elements, tdims, type); break;
    case s16: create_internal_array<short>(afarray, elements, tdims, type); break;
    case u16: create_internal_array<ushort>(afarray, elements, tdims, type); break;
  }
}

template<typename T>
void AfArray::create_internal_array(af_array afarray, Array elements, dim4 tdims, dtype type) {
  int count = elements.size();
  T casted_elements[count];
  for(int i = 0; i < count; i++) {
    casted_elements[i] = from_ruby<T>(elements[i]);
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

template<typename T>
void AfArray::create_internal_array_complex(af_array afarray, Array elements, dim4 tdims, dtype type) {
  int count = elements.size();
  T casted_elements[count];
  for(int i = 0; i < count; i++) {
    Object element = Object(elements[i]);
    double real = from_ruby<double>(element.call("real"));
    double imaginary = from_ruby<double>(element.call("imaginary"));
    casted_elements[i] = T(real, imaginary);
  };
  af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  this->set_c_array(afarray);
}

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
  return new AfArray(afarray);
}

AfArray* AfArray::multiply_internal(int value) {
  array afarray = this->c_array * value;
  return new AfArray(afarray);
}

AfArray* AfArray::add(AfArray other) {
  array afarray = this->c_array + other.get_c_array();
  return new AfArray(afarray);
}

AfArray* AfArray::div(AfArray other) {
  array afarray = this->c_array / other.get_c_array();
  return new AfArray(afarray);
}

AfArray* AfArray::randu(int rows, int cols, Symbol data_type) {
  dtype type = ruby_sym_to_dtype(data_type);
  array afarray = af::randu(cols, rows, type);
  return new AfArray(afarray);
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
