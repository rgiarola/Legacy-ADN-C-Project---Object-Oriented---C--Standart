#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_primeira_linha(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;

 ctrlvisual = *visual;

 if (ctrlvisual->linhaaux)
    {
     ctrlvisual->pos_ini = 0;
     VD_POPATR();
     VD_POPATR();
     ctrlvisual->flags |=
                (VIDEO_VISUAL_DISPLAY_PAGINA|
                 VIDEO_VISUAL_DISPLAY_PROMPT|
                 VIDEO_VISUAL_PEGA_LINHA_POS);
    }
  else
    if (ctrlvisual->linvisual)
       {
        if ((ctrlvisual->linvisual - (ctrlvisual->lintela-ctrlvisual->lini)) <= 0)
           {
            (*param)->VIDEO_repdisp = TRUE;
            (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_HOME);
            return(TRUE);
           }

        ctrlvisual->lintela = ctrlvisual->lini;
        ctrlvisual->linvisual = 0;
        VD_POPATR();
        VD_POPATR();
        ctrlvisual->flags |= (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
       }
 return(TRUE);
}

