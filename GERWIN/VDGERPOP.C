#include <INCVIDEO.H>

INT2 VIDEO_pop_descwin( VD_VOID )
{
#if defined(__VIDEO_ADM_WINDOW_CARGA_PARAMETROS)
 --VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win;
 --VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_win;
 *VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win =
 *VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_win;
 return(I(*VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win));
#else
 --VIDEO_pilha_desc_disp_win;
 --VIDEO_pilha_descritor_usado_win;
 *VIDEO_pilha_desc_disp_win = *VIDEO_pilha_descritor_usado_win;
 return(I(*VIDEO_pilha_desc_disp_win));
#endif
}
