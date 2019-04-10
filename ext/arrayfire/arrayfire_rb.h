#ifndef ARRAYFIRE_H
#define ARRAYFIRE_H 1

#ifdef __cplusplus

#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Data_Object.hpp"
#include "rice/Array.hpp"
#include "rice/Exception.hpp"

#include <arrayfire.h>
#include <stdio.h>
#include <ruby.h>
#include <math.h>
#include <map>
#include <algorithm>

extern Rice::Module rb_mArrayFire;

extern "C" {
#endif

void Init_ArrayFire();

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_H

af::dtype ruby_sym_to_dtype(Rice::Symbol data_type);
