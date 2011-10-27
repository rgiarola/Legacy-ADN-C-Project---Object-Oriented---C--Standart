#include <INCVIDEO.H>

INT2 VIDEO_TELA_seleciona_pasta(telas,param)
VIDEO_TELA_ENTRADA_DADOS **telas;
VIDEO_NUCLEO_SERV        **param;
{
 CTREE_cpybuf( (*telas)->imagem_ativa->arquivo, FALSE );
 return(TRUE);
}

