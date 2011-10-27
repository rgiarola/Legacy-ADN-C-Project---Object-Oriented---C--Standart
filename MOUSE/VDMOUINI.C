#include<INCVIDEO.H>

INT2 VIDEO_MOUSE_inicializa()
{
 INT2 ret;
#ifdef MS_C
 union REGS regs;
 regs.x.ax = VIDEO_MOUSE_INTBOT;
 int86(VIDEO_MOUSE_INT,&regs,&regs);
 ret = regs.x.bx;
#else
 _AX = VIDEO_MOUSE_INICIALIZACAO;
 geninterrupt(VIDEO_MOUSE_INT);
 ret = _BX;
#endif
 if (ret < 0 || ret > 3)
    ret = 0;
  else
    {
     VIDEO_MOUSE_ativo = ret;

     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_velocidade(W(0XF777));
     VIDEO_MOUSE_velocidade(W(0));
     VIDEO_MOUSE_dpi(VIDEO_MOUSE_vel_horizontal,VIDEO_MOUSE_vel_vertical);
     VIDEO_MOUSE_velocidade(W(0));
     VIDEO_MOUSE_deshabcursor();
    }
 return(ret);
}
