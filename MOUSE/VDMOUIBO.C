#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_intbot(botpres,numclick,col,lin)
INT2 *botpres,*numclick,
    *col    ,*lin;
{
 if (VIDEO_MOUSE_ativo)
    {
     WORD aux;
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_INTBOT;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
     aux = regs.x.ax;
     regs.x.ax = regs.x.bx;
     *numclick = regs.x.ax;
     *lin      = regs.x.dx;
     *col      = regs.x.cx;
     *botpres  = aux;
     *lin      = ((*lin>>3)+1);
     *col      = ((*col>>3)+1);
#else
     _AX = VIDEO_MOUSE_INTBOT;
     geninterrupt(VIDEO_MOUSE_INT);
     aux       = _AX,
     _AX       = _BX,
     *numclick = _AX,
     *lin      = _DX,
     *col      = _CX,
     *botpres  = aux;
     *lin      = ((*lin>>3)+1);
     *col      = ((*col>>3)+1);
    }
#endif
}

