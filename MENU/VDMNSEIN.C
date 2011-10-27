#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_inicio(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (inicial->opsel)
     if (inicial->opini > 0)
        {
         VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                        inicial->lin,inicial->lin,inicial->cor_opcao);
         inicial->opini = inicial->colatu =
         inicial->opsel = inicial->colpag = 0;
         inicial->lin = inicial->lini;
         inicial->col = inicial->coli;
         inicial->flagdispcol =
         inicial->flagdispop  = TRUE;
        }
     else
        VIDEO_MENU_seleciona_primeira(campos,param);
 return(TRUE);
}
