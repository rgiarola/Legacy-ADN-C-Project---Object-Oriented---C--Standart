#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_pagina_posterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 INT2                 offlin;

 ctrlvisual = *visual;

 if (!ctrlvisual->linhaaux)
    {
     offlin = ctrlvisual->linf - ctrlvisual->lini + 1;

     if (ctrlvisual->linvisual < (ctrlvisual->numlin-1))
         if ((((ctrlvisual->linvisual + offlin)-(ctrlvisual->lintela-ctrlvisual->lini)+offlin-1))
             > (ctrlvisual->numlin-1))
            {
             (*param)->VIDEO_repdisp = TRUE;
             (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_PGDN);
            }
          else
            {
             VD_POPATR();
             VD_POPATR();
             ctrlvisual->linvisual += offlin;
             ctrlvisual->flags   |=
                             (VIDEO_VISUAL_DISPLAY_PAGINA|VIDEO_VISUAL_DISPLAY_PROMPT);
            }
    }
  else
    if ((ctrlvisual->pos_ini + ctrlvisual->numlin) >= ctrlvisual->lido)
        VIDEO_mostra_mens_erro(VIDEO_VISUAL_fim_arquivo,TRUE);
      else
        {
         VD_POPATR();
         VD_POPATR();
         ctrlvisual->flags |=
                    (VIDEO_VISUAL_DISPLAY_PAGINA|
                     VIDEO_VISUAL_DISPLAY_PROMPT|
                     VIDEO_VISUAL_PEGA_PAG_POS  );
        }

 return(TRUE);
}

