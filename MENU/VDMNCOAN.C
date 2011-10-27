#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_col_anterior(campos,param,servico)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
INT2               servico;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if ((inicial->opsel - inicial->numlin) >= 0)
    {
     inicial->opini -= inicial->numlin;
     --inicial->colatu;
     if (servico == VIDEO_MENU_SEL_ESQ)
        inicial->opsel -= inicial->numlin;
      else
        {
         inicial->lin = inicial->linf;
         --inicial->opsel;
        }
     inicial->flagdispcol =
     inicial->flagdispop  = TRUE;
    }
  else
    {
     (*campos)->opselec = 0;
     return(FALSE);
    }
 return(TRUE);
}
