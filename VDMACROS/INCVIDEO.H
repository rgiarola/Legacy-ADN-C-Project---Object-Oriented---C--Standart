#include "CONFIG.ADN"


/*
   Aten‡„o !!!
   Problemas com M e n u
 */
#ifdef __VIDEO_BOX_CARGA_PARAMETROS
#undef __VIDEO_BOX_CARGA_PARAMETROS
#endif
#undef __VIDEO_BOX_CARGA_PARAMETROS

typedef unsigned char BYTE;           /* TIPO DE DADO BYTE*/

typedef unsigned char BOOLEAN;        /* TIPO DE DADO BOOLEAN*/

#ifdef VIDEO_UNIX
typedef short int          INT2;
typedef unsigned short int WORD;      /* TIPO DE DADO WORD*/
#endif

#ifdef VIDEO_DOS
typedef int          INT2;
typedef unsigned short int WORD;      /* TIPO DE DADO WORD*/
#endif

typedef unsigned long int  DWORD;     // TIPO DE DADO DWORD

#if defined(__CTREE)
#define CTREE_ATIVO
#ifdef VD_MULTUSER
  #include <EXTCTRE2.H>             // Modulo para REDE
#else
  #include <EXTCTREE.H>             // Modulo Mono-Usuario
#endif

#else

typedef long int INT4;

#endif

#ifndef __CTREE
  #include <stdio.h>
  #include <fcntl.h>
  #ifdef VIDEO_DOS
    #include <dos.h>
    #include <alloc.h>
  #endif
#endif


#include <ctype.h>

#ifdef VIDEO_DOS
  #ifdef MS_C
    #include <TIMEB.H>
    #include <TYPES.H>
    #include <UTIME.H>
    #include <DIRECT.H>
    #include <SIGNAL.H>
    #include <ERRNO.H>
  #else
    #include <DIR.H>
  #endif
#endif

#ifdef VIDEO_DOS
  #include <ERRNO.H>
  #include <IO.H>
  #include <PROCESS.H>
#endif

#include <limits.h>
#include <math.h>

#ifdef VIDEO_DOS
  #ifdef MS_C
    #include <MEMORY.H>
  #else
    #include <MEM.H>
  #endif
#endif

#include <string.h>

#ifdef VIDEO_DOS
  #ifdef MS_C
    #include <LIMITS.H>
  #else
    #include <VALUES.H>
  #endif
#endif

#ifdef VIDEO_DOS
  #include <STAT.H>
  #include <STDLIB.H>
  #include <TIME.H>
#endif

#ifdef VIDEO_UNIX
  #include <curses.h>
  #include <windows.h>
#endif

#include <VDVIDEO.VDO>
#include <CTREE.VDO>

// #include <ADNMEM.H>     // Suporte Extendido de Aloca‡‰os EMM / XMS

