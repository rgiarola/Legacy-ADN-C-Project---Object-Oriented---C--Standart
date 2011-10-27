#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_adm(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem;
 INT2              ret;

 imagem = (*tela)->imagem_ativa;

 if (imagem->tipotela > 1 && imagem->tipotela < 6)
    {
     (*param)->VIDEO_servrec = (imagem->flagimagem&VIDEO_TELA_STATUS) ?
                               VIDEO_DATABASE_INCLUSAO :
                               VIDEO_DATABASE_ALTERACAO;
     (*param)->VIDEO_repdisp = TRUE;
    }
 return(TRUE);
}




