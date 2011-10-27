#include <INCVIDEO.H>

#if defined(__VIDEO_ADMEM_CARGA_PARAMETROS)
       VIDEO_ADMEM_PARAMETROS *VIDEO_ADMEM_parametros =
                             VD_NILL(VIDEO_ADMEM_PARAMETROS);
#else
WORD      VIDEO_ADMEM_num_tab      = W(0),
          VIDEO_ADMEM_ct_stack     = W(0),
          VIDEO_ADMEM_livre        =
                       VIDEO_ADMEM_TAM_AREA_DEFAULT - VIDEO_ADMEM_DIRETORIO,
          VIDEO_ADMEM_tam_area     = VIDEO_ADMEM_TAM_AREA_DEFAULT,
          VIDEO_ADMEM_num_descmem  = VIDEO_ADMEM_NUM_DESCMEM_DEFAULT;

char      *VIDEO_ADMEM_area_buffer = VD_NILL(char),
          *VIDEO_ADMEM_topo        = VD_NILL(char),
          *VIDEO_ADMEM_base        = VD_NILL(char);
VD_VOID   **VIDEO_ADMEM_ultimo     = VD_NILL(VD_VOID *);

VIDEO_ADMEM_DESCRITOR  *VIDEO_ADMEM_area_mem;
#endif

