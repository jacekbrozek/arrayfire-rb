#include "arrayfire_rb.h"

using namespace Rice;
using namespace af;

class AfArray {
  private:
    array c_array;

  public:
    AfArray(array afarray);
    AfArray(Array dimensions, Array elements, Symbol data_type);
    void print();
    AfArray* multiply(Object other);
    AfArray* add(AfArray other);
    AfArray* div(AfArray other);
    static AfArray* randu(Array dimensions, Symbol data_type);
    static AfArray* randn(Array dimensions, Symbol data_type);
    static void set_seed(int seed);
    static int get_seed();
    AfArray* row(int index);
    AfArray* rows(int first, int last);
    AfArray* col(int index);
    AfArray* cols(int first, int last);
    AfArray* slice(int index);
    AfArray* slices(int first, int last);

  private:
    array get_c_array();
    static dim4 ruby_array_to_dimensions(Array dimensions);
    void set_c_array(af_array afarray);
    void set_c_array(const array& afarray);
    AfArray* multiply_internal(AfArray other);
    AfArray* multiply_internal(int value);
    template<typename T> void create_internal_array(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_long(af_array afarray, Array elements, dim4 tdims, dtype type);
    template<typename T> void create_internal_array_complex(af_array afarray, Array elements, dim4 tdims, dtype type);
};
