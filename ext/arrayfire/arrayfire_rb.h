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
#include "mnist_common.h"

extern Rice::Module rb_mArrayFire;

extern "C" {
#endif

void Init_ArrayFire();

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_H

af::dtype ruby_sym_to_dtype(Rice::Symbol data_type);
af::source ruby_sym_to_source(Rice::Symbol source);
af::matProp ruby_sym_to_opts(Rice::Symbol option);
Rice::Symbol dtype_to_ruby_sym(af::dtype data_type);
af::convMode ruby_sym_to_conv_mode(Rice::Symbol option);
af::convDomain ruby_sym_to_conv_domain(Rice::Symbol option);
af::normType ruby_sym_to_norm_type(Rice::Symbol norm_type);
af::Backend ruby_sym_to_backend(Rice::Symbol backend);
