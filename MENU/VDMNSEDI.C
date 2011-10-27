#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_direita(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (inicial->colpag == inicial->numpag)
     return(VIDEO_MENU_seleciona_col_posterior(campos,param,VIDEO_MENU_SEL_DIR));
   else
     if ((inicial->opsel + inicial->numlin) <= (inicial->numop - 1))
        {
         VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                        inicial->lin,inicial->lin,inicial->cor_opcao);
         ++inicial->colpag;
         ++inicial->colatu;
         inicial->opsel += inicial->numlin;
         inicial->col = inicial->coli + (inicial->colpag * inicial->tamcol);
         inicial->flagdispop = TRUE;
        }
      else
        {
         INT2 aux;
         aux = inicial->opsel - (inicial->lin - inicial->lini) +
               inicial->numlin;
         if (inicial->numop > aux)
            {
             VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                            inicial->lin,inicial->lin,inicial->cor_opcao);
             ++inicial->colpag;
             ++inicial->colatu;
             inicial->opsel = inicial->numop - 1;
             inicial->col = inicial->coli + (inicial->colpag * inicial->tamcol);
             inicial->flagdispop = TRUE;
             inicial->lin = inicial->numop - aux + inicial->lini - 1;
            }
        }

 return(TRUE);
}
