#include <INCVIDEO.H>

INT2 VIDEO_descarga_parametros(VD_VOID)
{
#if defined(__VIDEO_CARGA_PARAMETROS__)
 VIDEO_free_alloc_parametros(
	       VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl);
 VIDEO_free_alloc_parametros(
	       VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer);
 VIDEO_free_alloc_parametros(VIDEO_buffer_parametros_basicos);
/*========================================================================*/
#else
 VIDEO_free_alloc_parametros(VIDEO_filtro_buffertcl);
 VIDEO_free_alloc_parametros(VIDEO_ADMEM_area_buffer);
#endif
 return(TRUE);
}

