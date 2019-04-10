#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Array.hpp"

#include <arrayfire.h>
#include <stdio.h>
#include <ruby.h>
#include <math.h>
#include <map>
#include <algorithm>

#include "arrayfire_rb.h"
#include "test.h"

using namespace af;

Rice::Module rb_mArrayFire;

extern "C" void Init_arrayfire() {
  rb_mArrayFire = Rice::define_module("ArrayFire");

  Rice::Class rb_cArray = Rice::define_class_under(rb_mArrayFire, "Array")
    .define_method("info", &af_info);
}
