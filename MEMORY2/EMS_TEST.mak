#
# Turbo C makefile for TEST_EMS.C ( small model )
#
.c.obj:
     bcc -ml -c $<

ems_test.exe: ems_test.obj ems_err.obj ems4c_l.lib
     bcc -ml -M ems_test.obj ems_err.obj ems4c_l.lib

ems_test.obj: ems_test.c ems4c.h

ems_err.obj: ems_err.c ems4c.h

