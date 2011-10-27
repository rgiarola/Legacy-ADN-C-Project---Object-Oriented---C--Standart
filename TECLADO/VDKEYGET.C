#include <INCVIDEO.H>

INT2 VIDEO_getkey(ascii, scan)
BYTE    *ascii,
        *scan;
{
 char buffer[200];
#ifdef MS_C
 union REGS regs;
#endif

 if (VIDEO_CALC_backscan || VIDEO_CALC_backascii)
    {
     *ascii = VIDEO_CALC_backascii;
     *scan  = VIDEO_CALC_backscan;
     VIDEO_CALC_backscan = VIDEO_CALC_backascii = VD_NULO;
    }
  else
    {
#ifdef MS_C
     if (!kbhit())
        {
         if (VIDEO_TECLADO_funcao_auxiliar)
             (*VIDEO_TECLADO_funcao_auxiliar)(ascii,scan,FALSE);
         return(FALSE);
        }

     regs.h.al = 0XFF;
     regs.h.ah = 0X00;
     int86(0X16,&regs,&regs);
     *ascii = regs.h.al;
     *scan  = regs.h.ah;
#else
     _AL = 0XFF;
     _AH = 0X01;
     geninterrupt(0X16);
     if (_FLAGS&VIDEO_DOS_FLAG_ZERO)
        {
         if (VIDEO_TECLADO_funcao_auxiliar)
             (*VIDEO_TECLADO_funcao_auxiliar)(ascii,scan,FALSE);
         return(FALSE);
        }

     *ascii = _AL;
     *scan  = _AH;
     _AL = 0XFF;
     _AH = 0X00;
     geninterrupt(0X16);
#endif
    }

 if (VIDEO_TECLADO_funcao_auxiliar)
     (*VIDEO_TECLADO_funcao_auxiliar)(ascii,scan,FALSE);

 return(TRUE);
}


 
