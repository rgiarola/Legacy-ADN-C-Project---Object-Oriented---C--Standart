#include<INCVIDEO.H>

VD_VOID VIDEO_MOUSE_deshabcursor(VD_VOID)
{
 if (VIDEO_MOUSE_ativo)
    {
#ifdef MS_C
     union REGS regs;
     regs.x.ax = VIDEO_MOUSE_DESHABCURSOR;
     int86(VIDEO_MOUSE_INT,&regs,&regs);
#else
     _AX = VIDEO_MOUSE_DESHABCURSOR;
     geninterrupt(VIDEO_MOUSE_INT);
#endif
     VIDEO_MOUSE_cursor_ativo = FALSE;
    }
}
