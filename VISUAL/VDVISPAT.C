#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_pagina_anterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 INT2                 offlin;

 ctrlvisual = *visual;


 if (!ctrlvisual->linhaaux)
    {
     offlin = ctrlvisual->linf - ctrlvisual->lini + 1;

     if (ctrlvisual->linvisual)
         if (((ctrlvisual->linvisual - offlin)+(ctrlvisual->linf-ctrlvisual->lintela)+1-
               offlin)
             < 0)
            {
             (*param)->VIDEO_repdisp = TRUE;
             (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_PGUP);
            }
          else
            {
             VD_POPATR();
             VD_POPATR();
             ctrlvisual->linvisual -= offlin;
             ctrlvisual->flags   |=
                             (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
            }
    }
  else
    if (!ctrlvisual->pos_ini)
        VIDEO_mostra_mens_erro(VIDEO_VISUAL_inicio_arquivo,TRUE);
      else
        {
         VD_POPATR();
         VD_POPATR();
         ctrlvisual->flags |=
                        (VIDEO_VISUAL_DISPLAY_PAGINA|
                         VIDEO_VISUAL_DISPLAY_PROMPT|
                         VIDEO_VISUAL_PEGA_PAG_ANT  );
        }

 return(TRUE);
}

