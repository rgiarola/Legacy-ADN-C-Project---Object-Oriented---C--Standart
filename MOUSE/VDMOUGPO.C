#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_getpos(col,lin)
INT2  *col, *lin;
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_GETPOS;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
     *col = regs.x.cx;
     *lin = regs.x.dx;
#else
     _AX = VIDEO_MOUSE_GETPOS;
     geninterrupt(VIDEO_MOUSE_INT);
     *col = I(_CX);
     *lin = I(_DX);
#endif
     *col = ((*col>>3)+1);
     *lin = ((*lin>>3)+1);
    }
}
