#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_fim(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;
 INT2 aux;

 inicial = (*campos);

 aux = inicial->colatu - inicial->colpag + inicial->numpag + 1;

 if (inicial->opsel != (inicial->numop - 1))
    if (inicial->numop <= (inicial->numlin * aux))
       VIDEO_MENU_seleciona_ultima(campos,param);
     else
       {
        aux = inicial->numop % inicial->numlin;
        aux = inicial->numop / inicial->numlin + (aux > 0);
        inicial->opini = (aux - (inicial->numpag + 1)) * inicial->numlin;
        inicial->opsel = inicial->numop - 1;
        inicial->colpag = inicial->numpag;
        aux = inicial->numop % inicial->numlin;
        inicial->colatu = (inicial->numop / inicial->numlin) - (aux == 0);
        aux = aux ? --aux : inicial->numlin - 1;
        inicial->lin = inicial->lini + aux;
        inicial->col = inicial->coli + inicial->tamcol * inicial->numpag;
        inicial->flagdispcol =
        inicial->flagdispop = TRUE;
       }

 return(TRUE);
}
