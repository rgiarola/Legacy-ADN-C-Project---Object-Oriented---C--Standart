#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_pagina_anterior(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA  *pesquisa;
 INT2                      linatual,
                          linant,
                          cont;
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;
 pesquisa = *telapesq;

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
 imagem   = telacampos->imagens;

 linant   = pesquisa->linatual;

 if (pesquisa->linatual != (imagem->lini + 3))
    {
     VIDEO_CAMPO_TELA  *linhacampos,
                       *campos;
     INT2               contcampo;

     for (linatual = pesquisa->linatual;
                     linatual >= (imagem->lini + 3);linatual--)
         {
          if (CTREE_find(pesquisa->indice,pesquisa->segchave,
                                FIND_ANTERIOR,CT_LE_EXTRA_REPASSA) != 0)
               {
                --linatual;
                break;
               }
         }
	 ++linatual;

     linhacampos = PTR_CAST(VIDEO_CAMPO_TELA,
                            imagem->campos->VIDEO_campos);
     for (campos = linhacampos,contcampo = 0;
              contcampo < imagem->campos->VIDEO_numcampos;contcampo++,campos++)
          campos->lin = pesquisa->linatual = linatual;

     CTREE_find(pesquisa->indice,pesquisa->segchave,
                        FIND_PROXIMO,CT_LE_EXTRA_REPASSA);
    }

 VIDEO_PESQUISA_display_imagem(pesquisa,*param);

 VIDEO_PESQUISA_display_campos_anterior(pesquisa,*param);

 if (pesquisa->linatual < linant)
    {
     VIDEO_CAMPO_TELA  *linhacampos,
                       *campos;
     INT2               contcampo;
     campos = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);
     for (;pesquisa->linatual < linant;pesquisa->linatual++)
         {
          if (CTREE_find(pesquisa->indice,pesquisa->segchave,
                                FIND_PROXIMO,CT_LE_EXTRA_REPASSA))
			  break;
         }
     for (contcampo = 0;contcampo < imagem->campos->VIDEO_numcampos;
                                           contcampo++,campos++)
          campos->lin = pesquisa->linatual;
    }

 pesquisa->flagplanilha |= (VIDEO_PESQUISA_DISPLINHA |
                            VIDEO_PESQUISA_DISPCURSOR);

 return(TRUE);
}


