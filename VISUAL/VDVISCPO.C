#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_coluna_posterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *visual_local;
 visual_local = *visual;

 if (visual_local->refcol < (VIDEO_VISUAL_MAX_COL-10))
    {
     VD_POPATR();
     VD_POPATR();
     visual_local->flags |= (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
     ++visual_local->refcol;
    }

 return(TRUE);
}

