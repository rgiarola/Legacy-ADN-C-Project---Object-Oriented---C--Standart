#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_ultima(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;
 INT2 aux;

 inicial = (*campos);

 aux = inicial->colatu - inicial->colpag + inicial->numpag + 1;

 if (inicial->opsel != (inicial->numlin * aux - 1) &&
    (inicial->opsel != (inicial->numop - 1)))
    {
     VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                    inicial->lin,inicial->lin,inicial->cor_opcao);
     inicial->flagdispop = TRUE;
     if (inicial->numop >= (inicial->numlin *  aux))
        {
         inicial->col = inicial->coli + inicial->tamcol * inicial->numpag;
         inicial->lin = inicial->linf;
         inicial->colatu = aux - 1 ;
         inicial->colpag = inicial->numpag;
         inicial->opsel = inicial->numlin * aux - 1;
        }
      else
        {
         aux = inicial->numop % inicial->numlin;
         inicial->colatu = (inicial->numop / inicial->numlin) - (aux == 0);
         aux = aux ? --aux : inicial->numlin - 1;
         inicial->lin = inicial->lini + aux;
         inicial->opsel = inicial->numop - 1;
         inicial->col = inicial->coli + inicial->tamcol * inicial->numpag;
         inicial->colpag = inicial->numpag;
        }
    }
 return(TRUE);
}
