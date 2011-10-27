#include <INCVIDEO.H>

INT2 VIDEO_free_adm(endvar)
register VD_VOID **endvar;
{
 register VIDEO_ADMEM_DESCRITOR *ptrdesc;

#if defined(__VIDEO_ADMEM_CARGA_PARAMETROS)
 if ((ptrdesc = VIDEO_ADMEM_localiza(endvar)) >
     VD_NILL(VIDEO_ADMEM_DESCRITOR))
    {
     ptrdesc->endvar = VD_NILL(char *);
     VIDEO_ADMEM_parametros->VIDEO_ADMEM_livre += ptrdesc->tam;
     *(endvar) = VD_NILL(char);
     if (VIDEO_ADMEM_parametros->VIDEO_ADMEM_ultimo == endvar)
        {
         VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo += ptrdesc->tam;
         --VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_tab;
        }
     --VIDEO_ADMEM_parametros->VIDEO_ADMEM_ct_stack;
     return(TRUE);
    }
#else
 if ((ptrdesc = VIDEO_ADMEM_localiza(endvar)) >
     VD_NILL(VIDEO_ADMEM_DESCRITOR))
    {
     ptrdesc->endvar = VD_NILL(char *);
     VIDEO_ADMEM_livre += ptrdesc->tam;
     *(endvar) = VD_NILL(char);
     if (VIDEO_ADMEM_ultimo == endvar)
        {
         VIDEO_ADMEM_topo += ptrdesc->tam;
         --VIDEO_ADMEM_num_tab;
        }
     --VIDEO_ADMEM_ct_stack;
     return(TRUE);
    }
#endif
 return(FALSE);
}
