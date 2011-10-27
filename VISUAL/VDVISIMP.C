#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_imprime_arquivo(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV     **param;
{
 VD_PUSHWIN(1,80,1,25);
/*****************************************************************************
                          DISPLAY MODO DE OPERACAO
*****************************************************************************/
 VIDEO_CLEAR_PIC((*visual)->coli,(*visual)->colf-15,(*visual)->linf+4,(*visual)->linf+4,
                 VD_FORMATO(VD_VERMELHO,VD_INTER,VD_BLANK,VD_BRIL));
 VD_tprt_l((*visual)->coli+2,(*visual)->linf+4,VIDEO_VISUAL_modo_impress,0);

 VIDEO_VISUAL_impressao_arquivo(*visual);

 VD_POPWIN();

 (*param) ->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_PGUP);
 (*param) ->VIDEO_repdisp = TRUE;

 return(TRUE);
}


