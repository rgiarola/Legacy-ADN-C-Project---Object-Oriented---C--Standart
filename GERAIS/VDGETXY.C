#include <INCVIDEO.H>

INT2 VIDEO_getxy(col,lin)
INT2    *col,
       *lin;
{
#ifdef MS_C
 union REGS regs;
 regs.h.ah = 0X0F;
 int86(0X10,&regs,&regs);
 regs.h.ah = 0X03;
 int86(0X10,&regs,&regs);
 *lin = regs.h.dh;
 *col = regs.h.dl;
#else
 _AH = 0X0F;
 geninterrupt(0X10);
 _AH = 0X03;
 geninterrupt(0X10);
 *col = I(_DL);
 *lin = I(_DH);
#endif
 ++*col;
 ++*lin;
 return(TRUE);
}
