#ifndef TEST_H
#define TEST_H 1

#ifdef __cplusplus

#include <rice/Class.hpp>

extern Rice::Class rb_cTest;

extern "C" {
#endif

void Init_test();

#ifdef __cplusplus
}
#endif

#endif // CRYPTO_H
