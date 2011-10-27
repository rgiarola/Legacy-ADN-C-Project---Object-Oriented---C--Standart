#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_coluna_anterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *visual_local = *visual;

 if (visual_local->refcol)
    {
     VD_POPATR();
     VD_POPATR();
     visual_local->flags |= (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
     --visual_local->refcol;
    }
 return(TRUE);
}

