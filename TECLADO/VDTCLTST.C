#include <INCVIDEO.H>

INT2 VIDEO_testefiltcl(ascii,scan)
BYTE  *ascii,
      *scan;
{
 INT2 ret;

#if defined(__VIDEO_TCL_FILTRO_CARGA_PARAMETROS)
 ret = FALSE;
 if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl)
    {
     if (*ascii == '.')
         ret = (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                VIDEO_FILTCL_PONTO);
      else
        if (VIDEO_ISDIGIT(*ascii))
            ret = (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                   VIDEO_FILTCL_NUMERO);
      else
        if (VIDEO_ISCARACTER(*ascii))
           {
            if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                VIDEO_FILTCL_CARACTER)
               {
                ret = TRUE;
                if ((VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                     VIDEO_FILTCL_INVERTE) == VIDEO_FILTCL_INVERTE)
                   *ascii = *ascii & B5 ? *ascii & 0XDF : *ascii | B5;
                 else
                   if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                       VIDEO_FILTCL_MAIUSC)
                      *ascii &= 0XDF;
                    else
                      if (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                          VIDEO_FILTCL_MINUSC)
                         *ascii &= 0XDF;
               }
           }
      else
        if (*ascii == '+')
            ret = (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                   VIDEO_FILTCL_SINMAIS);
      else
        if (*ascii == '-')
            ret = (VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                   VIDEO_FILTCL_SINMENOS);

      if (!ret)
           ret = ((VIDEO_tcl_filtro_parametros->VIDEO_filtro_ent_tcl &
                   VIDEO_FILTCL_TABSKIP) &&
                   VIDEO_tcl_filtro_parametros->VIDEO_filtro_tabskiptcl &&
                   VIDEO_testa_tabskip(*ascii,*scan,
                   VIDEO_tcl_filtro_parametros->VIDEO_filtro_tabskiptcl));
    }
  else
   ret = TRUE;
#else
 ret = FALSE;
 if (VIDEO_filtro_ent_tcl)
    {
     if (*ascii == '.')
         ret = (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_PONTO);
      else
        if (VIDEO_ISDIGIT(*ascii))
            ret = (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_NUMERO);
      else
        if (VIDEO_ISCARACTER(*ascii))
           {
            if (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_CARACTER)
               {
                ret = TRUE;
                if ((VIDEO_filtro_ent_tcl & VIDEO_FILTCL_INVERTE) ==
                    VIDEO_FILTCL_INVERTE)
                   *ascii = *ascii & VD_B5 ? *ascii & 0XDF : *ascii | VD_B5;
                 else
                   if (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_MAIUSC)
                      *ascii &= 0XDF;
                    else
                      if (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_MINUSC)
                         *ascii &= 0XDF;
               }
           }
      else
        if (*ascii == '+')
            ret = (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_SINMAIS);
      else
        if (*ascii == '-')
            ret = (VIDEO_filtro_ent_tcl & VIDEO_FILTCL_SINMENOS);

      if (!ret)
           ret = ((VIDEO_filtro_ent_tcl & VIDEO_FILTCL_TABSKIP) &&
                  VIDEO_filtro_tabskiptcl &&
                  VIDEO_testa_tabskip(*ascii,*scan,VIDEO_filtro_tabskiptcl));
    }
  else
   ret = TRUE;
#endif
 return(ret);
}
