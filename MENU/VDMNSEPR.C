#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_primeira(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (inicial->opsel != (inicial->numlin *
                       (inicial->colatu - inicial->colpag)))
    {
     VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                    inicial->lin,inicial->lin,inicial->cor_opcao);
     inicial->colatu -= inicial->colpag;
     inicial->opsel = inicial->numlin * inicial->colatu;
     inicial->lin = inicial->lini;
     inicial->col = inicial->coli;
     inicial->colpag = 0;
     inicial->flagdispop = TRUE;
    }
 return(TRUE);
}
