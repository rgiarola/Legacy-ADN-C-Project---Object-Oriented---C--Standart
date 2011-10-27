#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_dpi(col,lin)
INT2  col,lin;
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_DPI;
     regs.x.cx = col;
     regs.x.dx = lin;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
#else
     _AX = VIDEO_MOUSE_DPI;
     _DX = lin;
     _CX = col;
     geninterrupt(VIDEO_MOUSE_INT);
    }
#endif
}
