#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_linha_anterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 ctrlvisual = *visual;

 if (ctrlvisual->linvisual)
    {
     if (ctrlvisual->lintela == ctrlvisual->lini)
        {
          VD_POPATR();
          VD_POPATR();
          VIDEO_desce_win(ctrlvisual->coli,ctrlvisual->colf,
                         ctrlvisual->lini,ctrlvisual->linf-1,1);
          VD_PUSHATR(ctrlvisual->coli,ctrlvisual->colf,
                     ctrlvisual->lini,ctrlvisual->linf);
          --ctrlvisual->linvisual;
          ctrlvisual->flags |=
                         (VIDEO_VISUAL_DISPLAY_LINHA|VIDEO_VISUAL_DISPLAY_PROMPT);
        }
      else
        {
         --ctrlvisual->linvisual;
         --ctrlvisual->lintela;
         ctrlvisual->flags |= VIDEO_VISUAL_RESSET_PROMPT;
        }
    }
  else
    if (ctrlvisual->linhaaux)
       {
        if (ctrlvisual->pos_ini > 0)
           {
            VD_POPATR();
            VD_POPATR();
            ctrlvisual->flags |=
                       (VIDEO_VISUAL_DISPLAY_PAGINA|
                        VIDEO_VISUAL_DISPLAY_PROMPT|
                        VIDEO_VISUAL_PEGA_LINHA_ANT);
            --ctrlvisual->pos_ini;
           }
         else
           VIDEO_mostra_mens_erro(VIDEO_VISUAL_inicio_arquivo,TRUE);

       }

 return(TRUE);
}

