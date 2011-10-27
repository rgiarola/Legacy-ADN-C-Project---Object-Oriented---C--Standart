#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_linha_posterior(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 ctrlvisual = *visual;

 if (ctrlvisual->linvisual < (ctrlvisual->numlin-1))
    {
     if (ctrlvisual->lintela == ctrlvisual->linf)
        {
         VD_POPATR();
         VD_POPATR();
         VIDEO_sobe_win(ctrlvisual->coli,ctrlvisual->colf,
                        ctrlvisual->lini+1,ctrlvisual->linf,1);
         VD_PUSHATR(ctrlvisual->coli,ctrlvisual->colf,
                        ctrlvisual->lini,ctrlvisual->linf);
         ++ctrlvisual->linvisual;
         ctrlvisual->flags |=
                        (VIDEO_VISUAL_DISPLAY_LINHA|VIDEO_VISUAL_DISPLAY_PROMPT);
        }
      else
        {
         ++ctrlvisual->linvisual;
         ++ctrlvisual->lintela;
         ctrlvisual->flags |= VIDEO_VISUAL_RESSET_PROMPT;
        }
    }
  else
    if (ctrlvisual->linhaaux)
       {
        if ((ctrlvisual->pos_ini + ctrlvisual->numlin) < ctrlvisual->lido)
           {
            ++ctrlvisual->pos_ini;
            VD_POPATR();
            VD_POPATR();
            ctrlvisual->flags |=
                       (VIDEO_VISUAL_DISPLAY_PAGINA|
                        VIDEO_VISUAL_DISPLAY_PROMPT|
                        VIDEO_VISUAL_PEGA_LINHA_POS);
           }
         else
           VIDEO_mostra_mens_erro(VIDEO_VISUAL_fim_arquivo,TRUE);
       }

 return(TRUE);
}

