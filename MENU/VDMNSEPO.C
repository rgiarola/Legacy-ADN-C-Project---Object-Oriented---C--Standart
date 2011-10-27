#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_posterior(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (inicial->opsel != (inicial->numop - 1))
    {
     if (inicial->lin == inicial->linf)
        {
         if (inicial->colpag == inicial->numpag)
            return(VIDEO_MENU_seleciona_col_posterior(campos,param,VIDEO_MENU_SEL_POS));
          else
            {
             VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                            inicial->lin,inicial->lin,inicial->cor_opcao);
             ++inicial->colpag;
             ++inicial->colatu;
             ++inicial->opsel;
             inicial->lin = inicial->lini;
             inicial->col = inicial->coli +
                            (inicial->colpag * inicial->tamcol);
             inicial->flagdispop = TRUE;
            }
        }
      else
        {
         VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                        inicial->lin,inicial->lin,inicial->cor_opcao);
         ++inicial->opsel;
         ++inicial->lin;
         inicial->flagdispop = TRUE;
        }
    }
  else
    {
     (*campos)->opselec = 0;
     return(FALSE);
    }

 return(TRUE);
}
