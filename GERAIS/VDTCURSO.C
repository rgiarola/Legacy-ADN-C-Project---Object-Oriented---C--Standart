#include <INCVIDEO.H>

INT2 VIDEO_tcursor(mlini,mlinf)
INT2    mlini,
       mlinf;
{
#ifdef MS_C
 union REGS regs;
 regs.h.ah = 0X01;
 regs.h.ch = B(mlini);
 regs.h.cl = B(mlinf);
 int86(0X10,&regs,&regs);
#else
 _CH = B(mlini);
 _CL = B(mlinf);
 _AH = 1;
 geninterrupt(0X10);
#endif
 return(TRUE);
}

