#include <INCVIDEO.H>

INT2 VIDEO_TELA_troca_serv_teclas(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 INT2              servrec;
 VIDEO_NUCLEO_SERV *nucleo;

 nucleo = *param;

 switch(nucleo->VIDEO_servrec)
  {
    case I(VD_MTTECLA(VD_NULO,F10)):servrec = I(VD_MTTECLA(VD_NULO,ALT_S))    ;
                                    break;
    case I(VD_MTTECLA(VD_NULO,F9 )):servrec = I(VD_MTTECLA(VD_NULO,ALT_E))    ;
                                    break;
    case I(VD_MTTECLA(VD_NULO,F8 )):servrec = I(VD_MTTECLA(VD_NULO,ALT_I))    ;
                                    break;
    case I(VD_MTTECLA(VD_NULO,F7 )):servrec = I(VD_MTTECLA(VD_NULO,ALT_O))    ;
                                    break;
    case I(VD_MTTECLA(VD_NULO,F6 )):servrec = I(VD_MTTECLA(VD_NULO,ALT_MAIS)) ;
                                    break;
    case I(VD_MTTECLA(VD_NULO,F5 )):servrec = I(VD_MTTECLA(VD_NULO,ALT_MENOS));
                                    break;

    default :servrec = VD_NULO;
   }

 if (servrec)
    {
     nucleo->VIDEO_servrec = servrec;
     nucleo->VIDEO_repdisp = TRUE;
    }

 return(TRUE);
}


