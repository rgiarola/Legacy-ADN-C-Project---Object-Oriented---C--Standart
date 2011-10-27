#include <INCVIDEO.H>

INT2 VIDEO_gtxy(col,lin)
INT2    col,
       lin;
{
#ifdef VIDEO_DOS
  #ifdef MS_C
   union REGS regs;
   regs.h.ah = 0X0F;
   int86(0X10,&regs,&regs);
   regs.h.dh = --lin;
   regs.h.dl = --col;
   regs.h.ah = 0X02;
   int86(0X10,&regs,&regs);
  #else
   _AH = 0X0F;
   geninterrupt(0X10);
   _DH = --lin;
   _DL = --col;
   _AH = 0X02;
   geninterrupt(0X10);
  #endif
#endif

#ifdef VIDEO_UNIX
 wmove(VIDEO_video_unix,lin-1,col-1);
#endif

 return(TRUE);
}

