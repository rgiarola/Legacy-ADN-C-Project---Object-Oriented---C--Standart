#include <INCVIDEO.H>

INT2 VIDEO_insfiltcl(ascii,scan)
BYTE  ascii,
      scan;
{
 INT2  *aux;

#if defined(__VIDEO_TCL_FILTRO_CARGA_PARAMETROS)
 aux = VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbuffin;

 if (aux == (VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl +
            (VIDEO_TAMBUFTCL - 1)))
     aux = VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl;
   else
     ++aux;

 if (aux == VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini)
    return(FALSE);

 *(VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbuffin) =
   W(W(ascii)|W(W(scan)>>8));
 VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbuffin = aux;
 #else
 aux = VIDEO_filtro_tclbuffin;

 if (aux == (VIDEO_filtro_buffertcl + (VIDEO_TAMBUFTCL - 1)))
     aux = VIDEO_filtro_buffertcl;
   else
     ++aux;

 if (aux == VIDEO_filtro_tclbufini)
    return(FALSE);

 *(VIDEO_filtro_tclbuffin) = W(W(ascii)|W(W(scan)<<8));
 VIDEO_filtro_tclbuffin = aux;
#endif
 return(TRUE);
}


