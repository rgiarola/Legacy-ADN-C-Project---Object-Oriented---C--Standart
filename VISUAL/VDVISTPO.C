#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_tab_posterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *visual_local = *visual;

 if (visual_local->refcol < (VIDEO_VISUAL_MAX_COL-1))
    {
     if ((*param)->VIDEO_servrec == VD_MTTECLA(VD_TAB,TABSCAN))
         visual_local->refcol = visual_local->refcol + 16 <= (VIDEO_VISUAL_MAX_COL-1) ?
                              visual_local->refcol + 16 : (VIDEO_VISUAL_MAX_COL-1);
       else
         visual_local->refcol = 80;

     VD_POPATR();
     VD_POPATR();
     visual_local->flags |= (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
    }
 return(TRUE);
}


