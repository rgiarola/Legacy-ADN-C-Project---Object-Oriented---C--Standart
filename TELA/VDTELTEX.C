#include <INCVIDEO.H>
/* ok*/

INT2 VIDEO_TELA_data_base_exc(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem;

 imagem = (*tela)->imagem_ativa;

 imagem->flagimagem &= ~VIDEO_TELA_SERVICO_EXECUTADO;    /* Controle Execucao.*/

 if (!(imagem->flagimagem&VIDEO_TELA_STATUS))
    {
     INT2 ret;

     if (VIDEO_TELA_funcao_exclusao)
        {
         ATIVA_BUF_DADOS;
         if (!VIDEO_TELA_funcao_exclusao(VIDEO_EXCLUSAO_PASSO1,
                                         imagem->arquivo,
                                         CTREE_filbuf(imagem->arquivo)))
             return(TRUE);
        }

     VD_tprt_l   (imagem->coli+21,imagem->linf,VIDEO_texto_exclusao,
                  VD_FORMATO(VD_VERDE,VD_NORMAL,VD_BLANK ,VD_BRIL));
     VD_plotcarac(imagem->coli+20,imagem->linf,'E',
                  VD_FORMATO(VD_VERDE,VD_NORMAL,VD_MARROM,VD_BRIL));

     if (imagem->flagimagem&VIDEO_TELA_FLAGCONFDELECAO)
         if (VD_telaconf((80-strlen(VIDEO_CONF_EXC_REGISTRO))/2,
                          10,VIDEO_CONF_EXC_REGISTRO,VIDEO_COR_EXC_REGISTRO) != 1)
            {
             VD_tprt_l   (imagem->coli+21,imagem->linf,VIDEO_texto_exclusao,
                          VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK ,VD_BRIL));
             VD_plotcarac(imagem->coli+20,imagem->linf,'E',
                          VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
             return(TRUE);
            }

     ATIVA_BUF_DADOS;
     DATABASE_ReReadRecord(CTREE_tmpfil(imagem->arquivo),
                           CTREE_filbuf(imagem->arquivo));

     if ((*tela)->imagem_accept < ((*tela)->num_imagens-1))
        VIDEO_TELA_data_base_exsub(*tela,imagem,FALSE);

     if (VIDEO_TELA_funcao_exclusao)
        {
         ATIVA_BUF_DADOS;
         if (!VIDEO_TELA_funcao_exclusao(VIDEO_EXCLUSAO_PASSO2,
                                         imagem->arquivo,
                                         CTREE_filbuf(imagem->arquivo)))
             return(TRUE);
        }

     if( (ret=CTREE_dlrec(imagem->arquivo)) != FALSE)
         {
          char   buffer[200];
          sprintf(buffer,CTREE_MENS_mens_padrao_err,
						 VIDEO_erro_exclusao,
						 (VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
                         ret,isam_err);
		  VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_exclusao);

          VD_tprt_l   (imagem->coli+21,imagem->linf,VIDEO_texto_exclusao,
                       VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK ,VD_BRIL));
          VD_plotcarac(imagem->coli+20,imagem->linf,'E',
                       VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
          return(TRUE);
         }

     if (VIDEO_TELA_funcao_exclusao)
        {
         ATIVA_BUF_DADOS;
         if (!VIDEO_TELA_funcao_exclusao(VIDEO_EXCLUSAO_PASSO3,
                                         imagem->arquivo,
                                         CTREE_filbuf(imagem->arquivo)))
             return(TRUE);
        }

     VIDEO_TELA_seleciona_inclusao(tela,param);
     imagem->flagimagem |= (VIDEO_TELA_FLAGREGALT|VIDEO_TELA_SERVICO_EXECUTADO);
    }
 return(TRUE);
}



