#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_esquerda(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (!inicial->colpag)
    {
     if (inicial->opsel)
        return(VIDEO_MENU_seleciona_col_anterior(campos,param,VIDEO_MENU_SEL_ESQ));
      else
        {
         (*campos)->opselec = 0;
         return(FALSE);
        }
    }
  else
    {
     VIDEO_setatrib(inicial->col,inicial->col+inicial->tamdispop-1,
                    inicial->lin,inicial->lin,inicial->cor_opcao);
     --inicial->colpag;
     --inicial->colatu;
     inicial->opsel -= inicial->numlin;
     inicial->col = inicial->coli + (inicial->colpag * inicial->tamcol);
     inicial->flagdispop = TRUE;
    }
 return(TRUE);
}
