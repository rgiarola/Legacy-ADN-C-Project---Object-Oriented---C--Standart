#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_ultima_linha(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 INT2                 offlin;

 ctrlvisual = *visual;

 if (ctrlvisual->linhaaux)
    {
     ctrlvisual->pos_ini = 9999999L;
     VD_POPATR();
     VD_POPATR();
     ctrlvisual->flags |=
                (VIDEO_VISUAL_DISPLAY_PAGINA|
                 VIDEO_VISUAL_DISPLAY_PROMPT|
                 VIDEO_VISUAL_PEGA_PAG_POS);
    }
  else
    if (ctrlvisual->linvisual != (ctrlvisual->numlin-1))
       {
        offlin = ctrlvisual->linf - ctrlvisual->lini + 1;

        if (offlin > (ctrlvisual->numlin-1))
           {
            (*param)->VIDEO_repdisp = TRUE;
            (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_END);
            return(TRUE);
           }

        if ((ctrlvisual->linvisual + (ctrlvisual->linf - ctrlvisual->lintela)) >=
            (ctrlvisual->numlin-1))
           {
            (*param)->VIDEO_repdisp = TRUE;
            (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_END);
            return(TRUE);
           }

        ctrlvisual->lintela = ctrlvisual->linf;
        ctrlvisual->linvisual = ctrlvisual->numlin-1;
        VD_POPATR();
        VD_POPATR();
        ctrlvisual->flags |= (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
       }

 return(TRUE);
}

