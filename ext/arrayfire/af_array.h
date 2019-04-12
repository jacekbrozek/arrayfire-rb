#include "arrayfire_rb.h"

using namespace Rice;
using namespace af;

class AfArray {
  private:
    array c_array;

  public:
    AfArray(array afarray);
    // AfArray(af_array afarray);
    AfArray(int rows, int cols, Array elements, Symbol data_type);
    void print();
    AfArray* multiply(Object other);
    AfArray* add(AfArray other);
    AfArray* div(AfArray other);
    static AfArray* randu(int rows, int cols, Symbol data_type);

  private:
    array get_c_array();
    void set_c_array(af_array afarray);
    void set_c_array(const array& afarray);
    AfArray* multiply_internal(AfArray other);
    AfArray* multiply_internal(int value);
};
