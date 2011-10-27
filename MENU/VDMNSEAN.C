#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_anterior(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (inicial->opsel)
    {
     if (inicial->lin == inicial->lini)
        {
         if (inicial->colpag)
            {
             VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                            inicial->lin,inicial->lin,inicial->cor_opcao);
             --inicial->colpag;
             --inicial->colatu;
             --inicial->opsel;
             inicial->col = inicial->coli + (inicial->colpag * inicial->tamcol);
             inicial->lin = inicial->linf;
             inicial->flagdispop = TRUE;
            }
          else
            VIDEO_MENU_seleciona_col_anterior(campos,param,VIDEO_MENU_SEL_ANT);
        }
      else
        {
         VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                        inicial->lin,inicial->lin,inicial->cor_opcao);
         --inicial->opsel;
         --inicial->lin;
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
