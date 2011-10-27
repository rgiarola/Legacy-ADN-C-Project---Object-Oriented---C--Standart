#include <INCVIDEO.H>

INT2 VIDEO_TELA_aborta_tudo(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_TELA_libera_subfile(*tela,FALSE);

 if (!((*tela)->flagtela&VIDEO_TELA_SALVATELA))
    VD_POPWIN();

 return(FALSE);
}
