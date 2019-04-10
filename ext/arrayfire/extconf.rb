require "mkmf-rice"


$CPPFLAGS += ' -I/opt/arrayfire/include'

have_library('afcpu')

create_makefile("arrayfire/arrayfire")
