#include <INCVIDEO.H>

VIDEO_ADMEM_DESCRITOR *VIDEO_ADMEM_localiza(endvar)
register VD_VOID **endvar;
{
#if defined(__VIDEO_ADMEM_CARGA_PARAMETROS)
 register VIDEO_ADMEM_DESCRITOR *cont =
          VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_mem;
#else
 register VIDEO_ADMEM_DESCRITOR *cont = VIDEO_ADMEM_area_mem;
#endif
 register INT2            num = 0;

 do
  {
   if ((cont)->endvar == endvar) 
      return(cont);
   ++cont;
#if defined(__VIDEO_ADMEM_CARGA_PARAMETROS)
  }while(++num < VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_tab);
#else
  }while(++num < VIDEO_ADMEM_num_tab);
#endif
 return(VD_NILL(VIDEO_ADMEM_DESCRITOR));
}

