#include <INCVIDEO.H>

INT2 VIDEO_box(coli,colf,lini,linf,cor,flagwin,carac)
INT2           coli, colf,
              lini, linf;
BYTE          cor;
INT2           flagwin;
char          carac;
{
 if (VIDEO_teste_4(coli,colf,lini,linf) && (flagwin >= 0) && (flagwin < 3))
    {
     char *pointer, *pointercol, *pointerlin;

#if defined(__VIDEO_BOX_CARGA_PARAMETROS)
     pointercol = (&VIDEO_box_parametros->VIDEO_conec_col_dupla + flagwin);
     pointerlin = (&VIDEO_box_parametros->VIDEO_conec_lin_dupla + flagwin);
#else
     pointercol = (&VIDEO_conec_col_dupla + flagwin);
     pointerlin = (&VIDEO_conec_lin_dupla + flagwin);
#endif

     if (flagwin & 2)
#if defined(__VIDEO_BOX_CARGA_PARAMETROS)
        VIDEO_box_parametros->VIDEO_conec_se_carac[0] =
        VIDEO_box_parametros->VIDEO_conec_sd_carac[0] =
        VIDEO_box_parametros->VIDEO_conec_ie_carac[0] =
        VIDEO_box_parametros->VIDEO_conec_id_carac[0] =
#else
        VIDEO_conec_se_carac[0] =
        VIDEO_conec_sd_carac[0] =
        VIDEO_conec_ie_carac[0] =
        VIDEO_conec_id_carac[0] =
#endif
        *pointercol = *pointerlin = carac;


#if defined(__VIDEO_BOX_CARGA_PARAMETROS)
     pointer = (&VIDEO_box_parametros->VIDEO_conec_se_dupla[0] + (flagwin * 8));
#else
     pointer = (&VIDEO_conec_se_dupla[0] + (flagwin * 8));
#endif

     VD_tprt_l(coli,lini,pointer  ,cor);
     VD_tprt_l(colf,lini,pointer+2,cor);
     VD_tprt_l(coli,linf,pointer+4,cor);
     VD_tprt_l(colf,linf,pointer+6,cor);

     VD_vertical(lini + 1,linf - 1,coli,*pointercol,cor);
     VD_vertical(lini + 1,linf - 1,colf,*pointercol,cor);
     VD_horizontal(coli + 1,colf - 1,lini,*pointerlin,cor);
     VD_horizontal(coli + 1,colf - 1,linf,*pointerlin,cor);

     return(TRUE);
    }
 return(FALSE);
}
