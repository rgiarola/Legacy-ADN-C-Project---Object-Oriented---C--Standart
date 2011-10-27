#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_adm_inclusao(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_CAMPO_TELA         *campo;
 INT2                      cont_campo,
                          cont_imagem;
 VIDEO_IMAGEMTELA         *imagem;
 INT2                      ret;

 imagem = (*tela)->imagem_ativa;

 if (VIDEO_TELA_funcao_inclusao)
    {
     ATIVA_BUF_DADOS;
     if (!VIDEO_TELA_funcao_inclusao(VIDEO_INCLUSAO_PASSO1,
                                     imagem->arquivo,
                                     CTREE_filbuf(imagem->arquivo)))
         return(TRUE);
    }

 if (!VIDEO_TELA_consiste_all(*tela,TRUE))
     return(TRUE);

 if (VIDEO_TELA_funcao_inclusao)
    {
     ATIVA_BUF_DADOS;
     if (!VIDEO_TELA_funcao_inclusao(VIDEO_INCLUSAO_PASSO2,
                                     imagem->arquivo,
                                     CTREE_filbuf(imagem->arquivo)))
         return(TRUE);
    }

 if ((ret = CTREE_adrec(imagem->arquivo)) != FALSE)
    {
	 char buffer[100];
	 sprintf(buffer,CTREE_MENS_mens_padrao_err,
					VIDEO_TELA_erro_addrec,
					(VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
					ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_addrec_tela);
     return(TRUE);
    }

 if (VIDEO_TELA_funcao_inclusao)
    {
     ATIVA_BUF_DADOS;
     if (VIDEO_TELA_funcao_inclusao(VIDEO_INCLUSAO_PASSO3,
                                    imagem->arquivo,
                                    CTREE_filbuf(imagem->arquivo)))
         return(TRUE);
    }

 imagem->flagimagem |= (VIDEO_TELA_DISPCAMPOS|VIDEO_TELA_FLAGRESETDISPLAY);

 if ((ret = CTREE_inbuf(imagem->arquivo)) != FALSE)
    {
	 char buffer[100];
	 sprintf(buffer,CTREE_MENS_mens_padrao_err,
					VIDEO_TELA_mens_inicbuffer,
					(VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
					ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_ini_buffer_addrec);
     return(TRUE);
    }

#ifdef DATABASE_CTREE
 imagem = (*tela)->imagens;
 cont_imagem = 0;
 do
  {
   VIDEO_TELA_ajusta_posicao(imagem);
   ++imagem;
  }while(++cont_imagem < (*tela)->num_imagens);
#endif

 for (imagem = (*tela)->imagens,ret = 0;ret < (*tela)->num_imagens &&
                                        imagem != (*tela)->imagem_ativa;ret++,imagem++)
      if (!strcmp(imagem->nmindarq,(*tela)->imagem_ativa->nmindarq))
         {
          (*tela)->imagem_ativa = imagem;
          (*tela)->imagem_accept = ret;
          break;
         }

 ((*tela)->imagem_accept+(*tela)->imagens)->campos->VIDEO_inicial=0;
 imagem->flagimagem |= VIDEO_TELA_FLAGREGALT;
 
 VIDEO_TELA_refresh_imagens(tela,param);
 return(TRUE);
}

