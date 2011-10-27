#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_seleciona_inclusao(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem;
 INT2              cont,
                  ret;

 imagem = (*tela)->imagem_ativa;

 imagem->flagimagem &= ~VIDEO_TELA_SERVICO_EXECUTADO;

 if (imagem->tipotela > 1 && imagem->tipotela < 6)
    {
	 if ((ret = CTREE_inbuf(imagem->arquivo)) != FALSE)
        {
         char buffer[100];
		 sprintf(buffer,CTREE_MENS_mens_padrao_err,
						VIDEO_TELA_mens_inicbuffer,
						(VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
						ret,isam_err);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_ini_buffer_inclusao);
         return(TRUE);
        }

     imagem = (*tela)->imagens;

     for (cont = 0;cont < (*tela)->num_imagens;cont++)
          if ((imagem+cont)->arquivo == (*tela)->imagem_ativa->arquivo)
             {
              (*tela)->imagem_accept = cont;
              break;
             }

     imagem = (*tela)->imagens;
     for (cont = 0;cont < (*tela)->num_imagens;cont++)
          if ((imagem+cont)->arquivo == (*tela)->imagem_ativa->arquivo)
              (imagem+cont)->flagimagem |=
                  (VIDEO_TELA_STATUS    |
                   VIDEO_TELA_DISPCAMPOS|
                   VIDEO_TELA_DISPIMAGEM|
                   VIDEO_TELA_SERVICO_EXECUTADO|
                   VIDEO_TELA_FLAGRESETDISPLAY);
     VIDEO_TELA_refresh_imagens(tela,param);
     ((*tela)->imagem_accept+(*tela)->imagens)->campos->VIDEO_inicial=0;
    }
 return(TRUE);
}

