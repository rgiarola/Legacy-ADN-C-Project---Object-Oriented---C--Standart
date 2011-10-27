#include <INCVIDEO.H>

INT2 VIDEO_getkeyfiltcl(ascii, scan)
BYTE    *ascii,
        *scan;
{
#if defined(__VIDEO_TCL_FILTRO_CARGA_PARAMETROS)
 if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini ==
     VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbuffin)
    {
#ifdef MS_C
      union REGS regs;
      regs.h.al = 0XFF;
      regs.h.ah = 0X01;
      int86(0X16,&regs,&regs);
      if (regs.x.cflag&VIDEO_DOS_FLAG_ZERO)
          return(FALSE);
      *ascii = regs.h.al;
      *scan  = regs.h.ah;
      regs.h.al = 0XFF;
      regs.h.ah = 0X00;
      int86(0X16,&regs,&regs);
#else
      _AL = 0XFF;
      _AH = 0X01;
      geninterrupt(0X16);
      if (_FLAGS&VIDEO_DOS_FLAG_ZERO)
          return(FALSE);
      *ascii = _AL;
      *scan  = _AH;
      _AL = 0XFF;
      _AH = 0X00;
      geninterrupt(0X16);
#endif
    }
  else
    {
     *ascii = B(*VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini);
     *scan  = B(*VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini>>8);
     if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini ==
        (VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl +
        (VIDEO_TAMBUFTCL - 1)))
         VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini =
         VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl;
       else
         ++VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini;
    }
#else
 if (VIDEO_filtro_tclbufini == VIDEO_filtro_tclbuffin)
    {
#ifdef MS_C
      union REGS regs;
      regs.h.al = 0XFF;
      regs.h.ah = 0X01;
      int86(0X16,&regs,&regs);
      if (regs.x.cflag&VIDEO_DOS_FLAG_ZERO)
          return(FALSE);
      *ascii = regs.h.al;
      *scan  = regs.h.ah;
      regs.h.al = 0XFF;
      regs.h.ah = 0X00;
      int86(0X16,&regs,&regs);
#else
      _AL = 0XFF;
      _AH = 0X01;
      geninterrupt(0X16);
      if (_FLAGS&VIDEO_DOS_FLAG_ZERO)
          return(FALSE);
      *ascii = _AL;
      *scan  = _AH;
      _AL = 0XFF;
      _AH = 0X00;
      geninterrupt(0X16);
#endif
    }
  else
    {
     *ascii = B(*VIDEO_filtro_tclbufini);
     *scan  = B(*VIDEO_filtro_tclbufini>>8);
     if (VIDEO_filtro_tclbufini ==
        (VIDEO_filtro_buffertcl + (VIDEO_TAMBUFTCL - 1)))
         VIDEO_filtro_tclbufini = VIDEO_filtro_buffertcl;
       else
         ++VIDEO_filtro_tclbufini;
    }
#endif
 return(VIDEO_testefiltcl(ascii,scan));
}
 
