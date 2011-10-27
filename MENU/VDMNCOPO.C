#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_col_posterior(campos,param,servico)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
INT2               servico;
{
 VIDEO_INFO_MENU *inicial;

 inicial = (*campos);

 if (((inicial->colatu - inicial->colpag + inicial->numpag + 1) *
      inicial->numlin) < inicial->numop)
    {
     if (inicial->opsel < (inicial->numop - 1))
        {
         ++inicial->colatu;
         inicial->opini += inicial->numlin;
         if (servico == VIDEO_MENU_SEL_DIR)
            {
             if ((inicial->opsel + inicial->numlin) < inicial->numop)
                inicial->opsel += inicial->numlin;
              else
                {
                 inicial->opsel = inicial->numop - 1;
                 inicial->lin = inicial->numop % inicial->numlin
                 + inicial->lini - 1;
                }
            }
           else
             {
              ++inicial->opsel;
              inicial->lin = inicial->lini;
             }
         inicial->flagdispcol =
         inicial->flagdispop  = TRUE;
        }
    }
  else
    {
     (*campos)->opselec = 0;
     return(FALSE);
    }

 return(TRUE);
}
