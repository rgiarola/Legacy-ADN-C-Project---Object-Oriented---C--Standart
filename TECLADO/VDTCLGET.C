#include <INCVIDEO.H>

INT2 VIDEO_getkbdfiltcl(ascii,scan)
BYTE  *ascii;
BYTE  *scan;
{
 INT2  flagtcl;

#if defined(__VIDEO_TCL_FILTRO_CARGA_PARAMETROS)
 do
  {
   flagtcl = (VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini ==
              VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbuffin);

   if (flagtcl)
      getkbd(ascii,scan);
    else
      {
       *ascii = B(*VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini);
       *scan  = B(*VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini>>8);
      }

   if (!VIDEO_testefiltcl(ascii,scan))
      continue;

   if (!flagtcl)
      {
       if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini ==
          (VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl +
          VIDEO_TAMBUFTCL-1))
            VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini =
            VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl;
         else
            ++VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini;
      }
   break;
  }while(TRUE);
#else
 do
  {
   flagtcl = (VIDEO_filtro_tclbufini == VIDEO_filtro_tclbuffin);

   if (flagtcl)
      getkbd(ascii,scan);
    else
      {
       *ascii = B(*VIDEO_filtro_tclbufini);
       *scan  = B(*VIDEO_filtro_tclbufini>>8);
      }

   if (!VIDEO_testefiltcl(ascii,scan))
      continue;

   if (!flagtcl)
      {
       if (VIDEO_filtro_tclbufini ==
          (VIDEO_filtro_buffertcl - VIDEO_TAMBUFTCL-1))
           VIDEO_filtro_tclbufini = VIDEO_filtro_buffertcl;
         else
           ++VIDEO_filtro_tclbufini;
      }
   break;
  }while(TRUE);
#endif
 return(TRUE);
}
