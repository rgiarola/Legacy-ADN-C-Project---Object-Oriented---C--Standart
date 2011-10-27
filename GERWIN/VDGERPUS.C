#include <INCVIDEO.H>

INT2 VIDEO_push_descwin( VD_VOID )
{
 BYTE desc;
#if defined(__VIDEO_ADM_WINDOW_CARGA_PARAMETROS)
 desc = *VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_win
      = *VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win;
 ++VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win;
 ++VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_win;
#else
 desc = *VIDEO_pilha_descritor_usado_win
      = *VIDEO_pilha_desc_disp_win;
 ++VIDEO_pilha_desc_disp_win;
 ++VIDEO_pilha_descritor_usado_win;
#endif
 return(I(desc));
}
