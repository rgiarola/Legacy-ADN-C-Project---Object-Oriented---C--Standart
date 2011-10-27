#include<INCVIDEO.H>

INT2 VIDEO_MOUSE_intbotpres(VD_VOID)
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_INTBOTPRES;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
     return(regs.x.ax>0);
#else
     _AX = VIDEO_MOUSE_INTBOTPRES;
     geninterrupt(VIDEO_MOUSE_INT);
     return(_AX>0);
    }
#endif
 return(FALSE);
}

