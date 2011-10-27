#include <INCVIDEO.H>

INT2 VIDEO_alloc_mem_adm(endvar,tamanho)
register VD_VOID **endvar;
register WORD    tamanho;
{
 register VIDEO_ADMEM_DESCRITOR *ptrdesc;

 *(endvar) = VD_NILL(char);

#if defined(__VIDEO_ADMEM_CARGA_PARAMETROS)

 if ((tamanho > VIDEO_ADMEM_parametros->VIDEO_ADMEM_livre) ||
     (VIDEO_ADMEM_parametros->VIDEO_ADMEM_ct_stack ==
      VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_descmem))
     return(FALSE);

 if (((VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo - tamanho) <
       VIDEO_ADMEM_parametros->VIDEO_ADMEM_base) ||
    (VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_tab ==
     VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_descmem))
     VIDEO_ADMEM_organiza();

 ptrdesc = (VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_mem +
            VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_tab),

 ptrdesc->endvar          = endvar,
 ptrdesc->tam             = tamanho,

 VIDEO_ADMEM_parametros->VIDEO_ADMEM_livre -= tamanho,
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo  -= tamanho,
 *(endvar) = ptrdesc->end = VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo + 1;
 ++VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_tab;
 ++VIDEO_ADMEM_parametros->VIDEO_ADMEM_ct_stack;
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_ultimo = endvar;

#else

 if ((tamanho > VIDEO_ADMEM_livre) ||
     (VIDEO_ADMEM_ct_stack == VIDEO_ADMEM_num_descmem))
     return(FALSE);

 if (((VIDEO_ADMEM_topo - tamanho) < VIDEO_ADMEM_base) ||
    (VIDEO_ADMEM_num_tab == VIDEO_ADMEM_num_descmem))
     VIDEO_ADMEM_organiza();

 ptrdesc                  = (VIDEO_ADMEM_area_mem + VIDEO_ADMEM_num_tab),
 ptrdesc->endvar          = (VD_VOID **) endvar,
 ptrdesc->tam             = tamanho,
 VIDEO_ADMEM_livre       -= tamanho,
 VIDEO_ADMEM_topo        -= tamanho,
 *(endvar) = ptrdesc->end = VIDEO_ADMEM_topo + 1,
 ++VIDEO_ADMEM_num_tab,
 ++VIDEO_ADMEM_ct_stack,
 VIDEO_ADMEM_ultimo = (VD_VOID **) endvar;
#endif
 return(TRUE);
}  
