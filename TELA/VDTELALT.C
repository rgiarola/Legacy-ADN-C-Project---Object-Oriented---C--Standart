#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_adm_alteracao(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem;
 INT2              ret;

 imagem = (*tela)->imagem_ativa;

 imagem->flagimagem &= ~VIDEO_TELA_SERVICO_EXECUTADO;

 if (VIDEO_TELA_funcao_alteracao)
    {
     ATIVA_BUF_DADOS;
     if (!VIDEO_TELA_funcao_alteracao(VIDEO_ALTERACAO_PASSO1,
                                      imagem->arquivo,
                                      CTREE_filbuf(imagem->arquivo)))
         return(TRUE);
    }

 if (!VIDEO_TELA_consiste_all(*tela,TRUE))
     return(TRUE);

 if (VIDEO_TELA_funcao_alteracao)
    {
     ATIVA_BUF_DADOS;
     if (!VIDEO_TELA_funcao_alteracao(VIDEO_ALTERACAO_PASSO2,
                                      imagem->arquivo,
                                      CTREE_filbuf(imagem->arquivo)))
         return(TRUE);
    }

 if ((ret = CTREE_rewrec(imagem->arquivo)) != FALSE)
    {
     char buffer[200];
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    VIDEO_TELA_erro_rewrec,
                    (VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_rewrec_tela);
    }

 if (VIDEO_TELA_funcao_alteracao)
    {
     ATIVA_BUF_DADOS;
     if (!VIDEO_TELA_funcao_alteracao(VIDEO_ALTERACAO_PASSO3,
                                      imagem->arquivo,
                                      CTREE_filbuf(imagem->arquivo)))
         return(TRUE);
    }

 VD_tprt_l(imagem->colf-10,imagem->linf,VIDEO_texto_salva,
                  VD_FORMATO(VD_VERDE,VD_NORMAL,VD_BLANK,VD_BRIL));
 VIDEO_espera(20);

 VD_tprt_l(imagem->colf-10,imagem->linf,VIDEO_texto_salva,
                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
 VD_plotcarac(imagem->colf-10,imagem->linf,'S',
                                     VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
 
 imagem->flagimagem |= (VIDEO_TELA_FLAGREGALT|VIDEO_TELA_SERVICO_EXECUTADO);

 return(TRUE);
}

