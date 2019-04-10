#include <iostream>

#include "arrayfire_rb.h"
#include "test.h"

using namespace Rice;

Class rb_cTest;

void says(const char * str) {
  std::cout << str << std::endl;
}

extern "C" void Init_test() {
  rb_cTest = define_class_under(rb_mArrayFire, "Test")
    .define_singleton_method("says", &says);
}

