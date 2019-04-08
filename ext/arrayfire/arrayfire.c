#include "arrayfire.h"

VALUE rb_mArrayfire;

void
Init_arrayfire(void)
{
  rb_mArrayfire = rb_define_module("Arrayfire");
}
