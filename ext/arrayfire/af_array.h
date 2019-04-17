#include "arrayfire_rb.h"

using namespace Rice;
using namespace af;

class AfArray {
  private:
    array c_array;

  public:
    AfArray(af_array afarray);
    AfArray(array afarray);
    AfArray(Array dimensions, Array elements, Symbol data_type);
    void print();
    AfArray* multiply(Object other);
    AfArray* multiply_assign(Object other);
    AfArray* add(Object other);
    AfArray* add_assign(Object other);
    AfArray* div(Object other);
    AfArray* div_assign(Object other);
    AfArray* sub(Object other);
    AfArray* sub_assign(Object other);
    static AfArray* randu(Array dimensions, Symbol data_type);
    static AfArray* randn(Array dimensions, Symbol data_type);
    static AfArray* constant(Object value, Array dimensions, Symbol data_type);
    static AfArray* range(int seq_dim, Array dimensions, Symbol data_type);
    static void set_seed(int seed);
    static int get_seed();
    AfArray* row(int index);
    AfArray* rows(int first, int last);
    AfArray* col(int index);
    AfArray* cols(int first, int last);
    AfArray* slice(int index);
    AfArray* slices(int first, int last);
    AfArray* lookup(Array idx);
    AfArray* real();
    AfArray* imag();
    AfArray* conjg();
    AfArray* diag(int num = 0, bool extract = true);
    AfArray* lower(bool is_unit_diag = false);
    AfArray* upper(bool is_unit_diag = false);
    AfArray* cast(Symbol data_type);
    static AfArray* identity(Array dimensions, Symbol data_type);
    static AfArray* iota(Array dimensions, Array tile_dimensions, Symbol data_type);

  private:
    array get_c_array();
    static dim4 ruby_array_to_dimensions(Array dimensions);
    static int* ruby_array_to_ints(Array rb_array);
    void set_c_array(af_array afarray);
    void set_c_array(const array& afarray);
    AfArray* multiply_internal(AfArray other);
    AfArray* multiply_internal(int value);
    AfArray* multiply_assign_internal(AfArray other);
    AfArray* multiply_assign_internal(int value);
    AfArray* add_internal(AfArray other);
    AfArray* add_internal(int value);
    AfArray* add_assign_internal(AfArray other);
    AfArray* add_assign_internal(int value);
    AfArray* div_internal(AfArray other);
    AfArray* div_internal(int value);
    AfArray* div_assign_internal(AfArray other);
    AfArray* div_assign_internal(int value);
    AfArray* sub_internal(AfArray other);
    AfArray* sub_internal(int value);
    AfArray* sub_assign_internal(AfArray other);
    AfArray* sub_assign_internal(int value);
    template<typename T> void create_internal_array(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_long(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_complex(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> static T cast_ruby_to(Object ruby_object);
    template<typename T> static T cast_ruby_to_long(Object ruby_object);
    template<typename T> static T cast_ruby_to_complex(Object ruby_object);
};
