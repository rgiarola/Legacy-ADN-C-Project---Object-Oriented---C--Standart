#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_velocidade(velocidade)
INT2  velocidade;
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_VELOCIDADE;
     regs.x.dx = velocidade;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
#else
     _AX = VIDEO_MOUSE_VELOCIDADE;
     _DX = velocidade;
     geninterrupt(VIDEO_MOUSE_INT);
    }
#endif
}
