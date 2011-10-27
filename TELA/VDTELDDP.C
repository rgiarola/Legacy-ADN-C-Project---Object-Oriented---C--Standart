#include <INCVIDEO.H>
/* ok*/

INT2 VIDEO_TELA_dispara_display(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 (*tela)->imagem_ativa->flagimagem |= VIDEO_TELA_DISPCAMPOS;
 return(TRUE);
}

