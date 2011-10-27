#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_pagpos(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;
 INT2 aux1,
     aux2,
     aux3;

 inicial = (*campos);

 aux1 = inicial->numop % inicial->numlin;
 aux1 = inicial->numop / inicial->numlin + (aux1 > 0);
 aux2 = inicial->opini / inicial->numlin;

 if ((aux1 - aux2) >= ((inicial->numpag + 1) * 2)
      && (inicial->opsel + (inicial->numlin * (inicial->numpag + 1))) <
      inicial->numop)
    {
     INT2  auxloc;
     auxloc = (inicial->numlin * (inicial->numpag + 1));
     inicial->opini += auxloc;
     inicial->opsel += auxloc;
     inicial->colatu += (inicial->numpag + 1);
     inicial->flagdispcol =
     inicial->flagdispop  = TRUE;
    }
  else
     if ((aux1 - aux2) == (inicial->numpag + 1))
          VIDEO_MENU_seleciona_fim(campos,param);
        else
          {
           aux1 = inicial->numop % inicial->numlin;
           aux1 = inicial->numop / inicial->numlin + (aux1 > 0);
           inicial->opini = (aux1 - (inicial->numpag + 1)) * inicial->numlin;
           aux1 = inicial->numop % inicial->numlin;
           inicial->colatu = (inicial->numop / inicial->numlin) - (aux1 == 0);
           aux1 = aux1 ? --aux1 : inicial->numlin - 1;

           aux2 = inicial->colpag * inicial->numlin +
                  inicial->lin - inicial->lini;

           if ((inicial->opini + aux2) >= inicial->numop)
              {
               inicial->colpag = inicial->numpag;
               inicial->lin = inicial->lini + aux1;
               inicial->col = inicial->coli + inicial->tamcol * inicial->numpag;
               inicial->opsel = inicial->numop - 1;
              }
            else
              {
               inicial->colatu = inicial->opini / inicial->numlin +
                                 inicial->colpag;
               inicial->opsel = inicial->opini + aux2;
              }
           inicial->flagdispcol =
           inicial->flagdispop = TRUE;
          }
 return(TRUE);
}
