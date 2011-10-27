#include <INCVIDEO.H>
/* OK*/

INT2 VIDEO_TELA_seleciona_copia(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem;

 imagem = (*tela)->imagem_ativa;
 imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;

 CTREE_cpybuf( imagem->arquivo , TRUE );

 return(TRUE);
}

