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
  int count = elements.size();

  if(type == f32) {
    float casted_elements[count];
    for(int i = 0; i < count; i++) {
      casted_elements[i] = from_ruby<float>(elements[i]);
    };
    af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  } else if(type == f64) {
    double casted_elements[count];
    for(int i = 0; i < count; i++) {
      casted_elements[i] = from_ruby<double>(elements[i]);
    };
    af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  } else if(type == u16 or type == u32 or type == u64 or type == u8 or type == s16 or type == s32 or type == s64) {
    long int casted_elements[count];
    for(int i = 0; i < count; i++) {
      casted_elements[i] = from_ruby<long int>(elements[i]);
    };
    af_create_array(&afarray, casted_elements, tdims.ndims(), tdims.get(), type);
  }

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
