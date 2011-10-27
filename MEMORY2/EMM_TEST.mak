#
# Turbo C makefile for EMM_TEST.C ( small model )
#

.c.obj:
     bcc -ml -c $<

emm_test.exe: emm_test.obj ems_err.obj emm4c.obj ems4c_l.lib
     bcc -ml -M emm_test.obj ems_err.obj emm4c.obj ems4c_l.lib

emm_test.obj: emm_test.c ems4c.h

ems_err.obj: ems_err.c ems4c.h

emm4c.obj: emm4c.c emm4c.h
