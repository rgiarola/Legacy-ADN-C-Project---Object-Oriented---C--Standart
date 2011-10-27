#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_tab_anterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *visual_local = *visual;

 if (visual_local->refcol)
    {
     VD_POPATR();
     VD_POPATR();
     visual_local->flags |= (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
     if ((*param)->VIDEO_servrec == VD_MTTECLA(VD_NULO,TABSCAN))
         visual_local->refcol = visual_local->refcol - 16 >= 0 ?
                              visual_local->refcol - 16 : 0;
       else
         visual_local->refcol = 0;
    }
 return(TRUE);
}



