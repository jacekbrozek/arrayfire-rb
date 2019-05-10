require "mkmf-rice"

$CPPFLAGS += ' -I/opt/arrayfire/include'
$LIBS += ' -L/opt/arrayfire/lib'
$DLDFLAGS += ' -L/opt/arrayfire/lib'

have_library('af')

dir_config('/opt/arrayfire/lib')

create_makefile("arrayfire/arrayfire")
