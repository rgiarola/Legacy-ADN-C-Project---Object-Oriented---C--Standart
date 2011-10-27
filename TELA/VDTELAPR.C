#include <INCVIDEO.H>

VD_VOID VIDEO_TELA_ajusta_posicao(imagem)
VIDEO_IMAGEMTELA *imagem;
{
#ifndef DATABASE_CTREE

 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_CAMPO_TELA         *campo;
 INT2                      cont_campo,
                          cont_imagem;
 if (imagem->campos)
     for (cont_campo = 0,
          campo = PTR_CAST(VIDEO_CAMPO_TELA,
                      imagem->campos->VIDEO_campos);
                      cont_campo < imagem->campos->VIDEO_numcampos;
          campo++,cont_campo++)
          if ((consiste = campo->consiste) !=
               VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
             while(consiste->tipocons)
              {
               if ((consiste->tipocons ==
                    VIDEO_TELA_CONS_POSICIONA_DB) &&
                   (imagem->arquivo ==
                    CTREE_keyfil(consiste->objetocons.consdb->indice)))
                   {
                    if (consiste->objetocons.consdb->posicao)
                       DATABASE_FreeCurrentFileOffset(consiste->objetocons.consdb->posicao);
                    consiste->objetocons.consdb->posicao =
                    DATABASE_CurrentFileOffset(CTREE_tmpfil(imagem->arquivo));
                    break;
                   }
               ++consiste;
              }
#endif
}


