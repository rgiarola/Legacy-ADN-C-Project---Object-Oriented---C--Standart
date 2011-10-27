#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_pagant(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;
 INT2 aux1,
     aux2;

 inicial = (*campos);

 if (!inicial->opini)
     VIDEO_MENU_seleciona_primeira(campos,param);
   else
     if ((inicial->colatu - inicial->colpag - (inicial->numpag + 1)) >= 0)
        {
         INT2  auxloc;
         auxloc = (inicial->numlin * (inicial->numpag + 1));
         inicial->opini -= auxloc;
         inicial->opsel -= auxloc;
         inicial->colatu -= (inicial->numpag + 1);
         inicial->flagdispcol =
         inicial->flagdispop  = TRUE;
        }
      else
        if (inicial->opsel == inicial->opini)
            VIDEO_MENU_seleciona_inicio(campos,param);
          else
            {
             inicial->colatu = inicial->colpag;
             inicial->opsel = inicial->numlin * inicial->colatu +
                              inicial->lin - inicial->lini;
             inicial->opini = 0;
             inicial->flagdispcol =
             inicial->flagdispop  = TRUE;
            }
 return(TRUE);
}
