#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_fim_pagina(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 INT2                 offlin,
                     linf;

 ctrlvisual = *visual;
 offlin = ctrlvisual->linf-ctrlvisual->lini+1;

 if (offlin > ctrlvisual->numlin)
    linf = ctrlvisual->lini + ctrlvisual->numlin - 1;
  else
    linf = ctrlvisual->linf;

 if (ctrlvisual->lintela != ctrlvisual->linf)
	{
     offlin = linf - ctrlvisual->lintela;
     ctrlvisual->lintela = linf;
     ctrlvisual->linvisual += offlin;
     ctrlvisual->flags   |= VIDEO_VISUAL_RESSET_PROMPT;
	}

 return(TRUE);
}

