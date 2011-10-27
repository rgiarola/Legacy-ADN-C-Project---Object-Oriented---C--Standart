#include <INCVIDEO.H>

#if defined(__VIDEO_DIM_TELA_CARGA_PARAMETROS)
       VIDEO_DIM_TELA_PARAMETROS *VIDEO_dim_tela_parametros =
                      VD_NILL(VIDEO_DIM_TELA_PARAMETROS);
#else
INT2    VIDEO_maxcol = VIDEO_MAXCOL,
       VIDEO_maxlin = VIDEO_MAXLIN,
       VIDEO_minlin = VIDEO_MINLIN,
       VIDEO_mincol = VIDEO_MINCOL;
#endif

