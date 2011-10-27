#include <INCVIDEO.H>

#if defined(__VIDEO_TCL_FILTRO_CARGA_PARAMETROS)
       VIDEO_TCL_FILTRO_PARAMETROS *VIDEO_tcl_filtro_parametros =
                      VD_NILL(VIDEO_TCL_FILTRO_PARAMETROS);
#else
INT2 VIDEO_filtro_ent_tcl = I(0),
    *VIDEO_filtro_buffertcl,
    *VIDEO_filtro_tclbufini,
    *VIDEO_filtro_tclbuffin,
    *VIDEO_filtro_tabskiptcl = VIDEO_NILL(INT2);
#endif

INT2 (*VIDEO_TECLADO_funcao_auxiliar)() = VD_NULO;

VD_VOID (*VIDEO_save_screen)            (int (*funcao)() )       = VD_NULO;
VD_VOID (*VIDEO_trata_funcoes_especiais)(INT2 Local,INT2 Tecla)  = VD_NULO;

char display_save_screen_titulo[] = " N o v a   V i s „ o ";
char VIDEO_save_screen_ja_ativo   = FALSE;
int  VIDEO_save_screen_tempo      = 180;

