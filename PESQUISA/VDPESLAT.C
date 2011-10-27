#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_linha_anterior(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA  *pesquisa;
 INT2                      ret,arquivo,
                          tmpfil;
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;

 pesquisa = *telapesq;

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
 imagem   = telacampos->imagens;


 if ((ret = CTREE_find(pesquisa->indice,pesquisa->segchave,
                       FIND_ANTERIOR,CT_LE_EXTRA_REPASSA)) != 0)
    {
     char   buffer[200];
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    VIDEO_PESQ_mens_ini_arquivo,
                    (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(pesquisa->indice))->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,
                            ret != 101 && ret != 100       ?
                            VIDEO_ERRO_ini_arq_planilha_lat:
                            TRUE                           );
     return(TRUE);
    }

  VD_setatrib(imagem->coli+1,imagem->colf-1,
              pesquisa->linatual,pesquisa->linatual,
              PTR_CAST(VIDEO_CAMPO_TELA,
              imagem->campos->VIDEO_campos)->saida);

 if (pesquisa->linatual == (imagem->lini+3))
     VIDEO_desce_win(imagem->coli+1,imagem->colf-1,
                     imagem->lini+3,imagem->linf-3,1);
  else
   {
    VIDEO_CAMPO_TELA  *linhacampos,
                      *campos;
    INT2               contcampo;
    --pesquisa->linatual;
    linhacampos = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);
    for (campos = linhacampos,contcampo = 0;
         contcampo < imagem->campos->VIDEO_numcampos;contcampo++,campos++)
         campos->lin = pesquisa->linatual;
   }

 pesquisa->flagplanilha |= (VIDEO_PESQUISA_DISPLINHA |
                            VIDEO_PESQUISA_DISPCURSOR);

 return(TRUE);
}

