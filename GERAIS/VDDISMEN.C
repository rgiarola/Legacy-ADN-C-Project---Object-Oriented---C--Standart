#include <INCVIDEO.H>

INT2 VIDEO_TELA_display_mens(mensagem)
VIDEO_MENSAGEM *mensagem;
{
 INT2  ret,
      col ,lin;
 BYTE ascii,
      scan;

#ifdef APLIC_POS4000
 ret = VIDEO_PUSHWIN(1,40,mensagem->lin,mensagem->lin);
 VIDEO_CLEAR_PIC(1,40,mensagem->lin,mensagem->lin,7);
#else
 ret = VIDEO_PUSHWIN(mensagem->col,strlen(mensagem->mensagem) + mensagem->col,
                     mensagem->lin,mensagem->lin);
#endif


#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo && VIDEO_MOUSE_cursor_ativo)
     VIDEO_MOUSE_deshabcursor();
#endif

 VD_tprt_l(mensagem->col,mensagem->lin,mensagem->mensagem,mensagem->cor);

#ifdef VIDEO_UNIX
 VIDEO_UNIX_refresh_tela();
#endif

 VD_getxy(&col,&lin);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo)
    {
     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_flagtravado = TRUE;
     VIDEO_MOUSE_timetrav = FALSE;
    }
#endif

 VD_lepos(mensagem->col,mensagem->lin,&ascii,&scan);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo)
     VIDEO_MOUSE_deshabcursor();
#endif

 VD_gtxy(col,lin);
 if (ret >= 0)
    {
     VIDEO_POPWIN();
#ifdef VIDEO_UNIX
     VIDEO_UNIX_refresh_tela();
#endif
    }

 return(VD_MTTECLA(ascii,scan));
}
