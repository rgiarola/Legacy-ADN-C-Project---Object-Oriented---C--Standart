#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_selec_numtela(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 INT2 cont;

 if ((*tela)->imagem_accept < ((*tela)->num_imagens - 1))
    {
     ++(*tela)->imagem_accept;
     ((*tela)->imagens+(*tela)->imagem_accept)->flagimagem    |=
                                        (VIDEO_TELA_DISPIMAGEM|
                                         VIDEO_TELA_DISPCAMPOS);
     for (cont = 0;cont < (*tela)->imagem_accept;cont++)
          if (((*tela)->imagens+cont)->arquivo ==
              ((*tela)->imagens+(*tela)->imagem_accept)->arquivo)
             {
              ((*tela)->imagens+(*tela)->imagem_accept)->flagimagem |=
              (((*tela)->imagens+cont)->flagimagem&VIDEO_TELA_STATUS);
              return(TRUE);
             }
    }
 return(TRUE);
}

