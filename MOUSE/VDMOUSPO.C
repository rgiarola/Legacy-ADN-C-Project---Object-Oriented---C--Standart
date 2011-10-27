#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_setpos(col,lin)
INT2  col, lin;
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     col = ((col-1)<<3);
     lin = ((lin-1)<<3);
     regs.x.ax = VIDEO_MOUSE_SETPOS;
     regs.x.cx = col;
     regs.x.dx = lin;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
#else
     col = ((col-1)<<3);
     lin = ((lin-1)<<3);
     I(_CX) = col;
     I(_DX) = lin;
     _AX = VIDEO_MOUSE_SETPOS;
     geninterrupt(VIDEO_MOUSE_INT);
#endif
    }
}
