#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_display_campos_anterior(pesquisa,param)
VIDEO_PESQUISA_PLANILHA *pesquisa;
VIDEO_NUCLEO_SERV       *param;
{
 VIDEO_CAMPO_TELA         *linhacampos,
                          *campos;
 INT2                      numcampos,lini  ,linf,
                          indice,contlin,contcampo,
                          ret,tmpfil;
 char                     buffer[200];
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
 imagem   = telacampos->imagens;

 lini   = imagem->lini + 3;
 linf   = imagem->linf - 2;
 indice = pesquisa->indice;

 numcampos   = imagem->campos->VIDEO_numcampos;
 linhacampos = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);

 for (contlin = linf;contlin >= lini;contlin--)
     {
      for (campos = linhacampos,contcampo = 0;contcampo < numcampos;
                                            contcampo++,campos++)
           campos->lin = contlin;

      if (CTREE_find(indice,pesquisa->segchave,
                     FIND_ANTERIOR, CT_LE_EXTRA_REPASSA))
         {
          VIDEO_PESQUISA_display_imagem(pesquisa,param);
          CTREE_find(indice,pesquisa->segchave,
                     FIND_PRIMEIRO, CT_LE_EXTRA_REPASSA);
          VIDEO_PESQUISA_display_campos_posterior(pesquisa,param);
          break;
         }

      VIDEO_TELA_display_campos(linhacampos,numcampos,imagem->campos,
      VIDEO_FLAGVALIDA_CAMPO |
      VIDEO_FLAGUSER_CAMPO   |
      VIDEO_TELA_FLAGRESETDISPLAY );
      pesquisa->linatual = contlin;
     }

 return(TRUE);
}

