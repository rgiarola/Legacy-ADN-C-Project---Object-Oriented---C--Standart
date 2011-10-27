#include <INCVIDEO.H>

INT2 VIDEO_teste_cordenadas_x_y(teste)
INT2 teste;
{
 INT2 *ptrcoord;

 ptrcoord = &teste + 1;
                            
#if defined(__VIDEO_DIM_TELA_CARGA_PARAMETROS)
 switch(teste)
  {
   case VIDEO_TESTE_4_COORD:
          if ((*ptrcoord       < VIDEO_dim_tela_parametros->VIDEO_mincol) ||
              (*(ptrcoord + 1) > VIDEO_dim_tela_parametros->VIDEO_maxcol) ||
              (*(ptrcoord + 2) < VIDEO_dim_tela_parametros->VIDEO_minlin) ||
              (*(ptrcoord + 3) > VIDEO_dim_tela_parametros->VIDEO_maxlin) ||
              (*ptrcoord       > *(ptrcoord + 1)) ||
              (*(ptrcoord + 2) > *(ptrcoord + 3)))
              return(FALSE);
          break;
   case VIDEO_TESTE_2_COORD:
          if ((*ptrcoord       < VIDEO_dim_tela_parametros->VIDEO_mincol) ||
              (*ptrcoord       > VIDEO_dim_tela_parametros->VIDEO_maxcol) ||
              (*(ptrcoord + 1) < VIDEO_dim_tela_parametros->VIDEO_minlin) ||
              (*(ptrcoord + 1) > VIDEO_dim_tela_parametros->VIDEO_maxlin))
              return(FALSE);
          break;

   default: return(FALSE);
  }
#else
 switch(teste)
  {
   case VIDEO_TESTE_4_COORD:if ((*ptrcoord       < VIDEO_mincol)    ||
                                (*(ptrcoord + 1) > VIDEO_maxcol)    ||
                                (*(ptrcoord + 2) < VIDEO_minlin)    ||
                                (*(ptrcoord + 3) > VIDEO_maxlin)    ||
                                (*ptrcoord       > *(ptrcoord + 1)) ||
                                (*(ptrcoord + 2) > *(ptrcoord + 3)))
                                return(FALSE);
                            break;

   case VIDEO_TESTE_2_COORD:if ((*ptrcoord       < VIDEO_mincol) ||
                                (*ptrcoord       > VIDEO_maxcol) ||
                                (*(ptrcoord + 1) < VIDEO_minlin) ||
                                (*(ptrcoord + 1) > VIDEO_maxlin))
                                return(FALSE);
                            break;
   default : return(FALSE);
  }
#endif
 return(TRUE);
}



