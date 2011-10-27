#
# Turbo C makefile for EMS_STAT.C ( small model )
#
.c.obj:
     tcc -ms -c $<

ems_stat.exe: ems_stat.obj ems_err.obj ems4c_s.lib
     tcc -ms -M ems_stat.obj ems_err.obj ems4c_s.lib

ems_stat.obj: ems_stat.c ems4c.h

ems_err.obj: ems_err.c ems4c.h