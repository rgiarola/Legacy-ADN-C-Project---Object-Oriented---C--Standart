#include <INCVIDEO.H>

INT2 VIDEO_TELA_display_confirma(mensagem)
VIDEO_MENSAGEM *mensagem;
{
 INT2  ret,
       col  ,lin;
 BYTE  ascii,scan;
#ifdef VIDEO_UNIX
 INT2  old_flag_unix;
#endif

 ret = VIDEO_PUSHWIN(mensagem->col,strlen(mensagem->mensagem) + mensagem->col,
                     mensagem->lin,mensagem->lin);
#ifdef VIDEO_UNIX
 old_flag_video = VIDEO_UNIX_flag_video;
 VIDEO_UNIX_flag_video &= ~VIDEO_UNIX_AUTO_REFRESH;
#endif

 VD_tprt_l(mensagem->col,mensagem->lin,mensagem->mensagem,mensagem->cor);

#ifdef VIDEO_UNIX
     VIDEO_UNIX_refresh_tela();
#endif

 VD_getxy(&col,&lin);
 do
  {
   VD_lepos(mensagem->col+strlen(mensagem->mensagem),mensagem->lin,&ascii,&scan);
   if (ascii == 27)
      break;

   ascii &= ~0X20;
  }while((ascii != 'S') && (ascii != 'N'));

 VD_gtxy(col,lin);

 if (ret >= 0)
    {
     VIDEO_POPWIN();
#ifdef VIDEO_UNIX
     VIDEO_UNIX_refresh_tela();
#endif
    }

#ifdef VIDEO_UNIX
     VIDEO_UNIX_flag_video = old_flag_video;
#endif

 return(I(ascii));
}

