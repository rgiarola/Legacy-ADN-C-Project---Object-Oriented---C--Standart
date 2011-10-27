#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_habcursor()
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_HABCURSOR;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
#else
     _AX = VIDEO_MOUSE_HABCURSOR;
     geninterrupt(VIDEO_MOUSE_INT);
#endif
     VIDEO_MOUSE_cursor_ativo = TRUE;
    }
}
