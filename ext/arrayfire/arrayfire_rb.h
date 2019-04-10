#ifndef ARRAYFIRE_H
#define ARRAYFIRE_H 1

#ifdef __cplusplus

#include <rice/Module.hpp>

extern Rice::Module rb_mArrayFire;

extern "C" {
#endif

void Init_ArrayFire();

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_H
