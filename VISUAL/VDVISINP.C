#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_inicio_pagina(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 INT2                 offlin;

 ctrlvisual = *visual;

 if (ctrlvisual->lintela != ctrlvisual->lini)
	{
     offlin = ctrlvisual->lintela - ctrlvisual->lini;
     ctrlvisual->lintela = ctrlvisual->lini;
     ctrlvisual->linvisual -= offlin;
     ctrlvisual->flags   |= VIDEO_VISUAL_RESSET_PROMPT;
	}
 return(TRUE);
}

