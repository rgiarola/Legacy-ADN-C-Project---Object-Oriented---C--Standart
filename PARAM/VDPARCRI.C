RAMETROS)      ,
               sizeof(VIDEO_ADM_WINDOW_PARAMETROS) ,
               sizeof(VIDEO_TCL_FILTRO_PARAMETROS) },
     *tam = tot,
     desc,
     cont;
     BYTE    *ptrparam[] = {(BYTE *) &VIDEO_conec_se_dupla,
                            (BYTE *) &VIDEO_maxcol,
                            (BYTE *) &VIDEO_ADMEM_num_tab,
                            (BYTE *) &VIDEO_filtro_ent_tcl,
                            (BYTE *) &VIDEO_num_desc_win   };

 if ((desc = VD_cria(VIDEO_arquivo_parametros_basicos)) < 0)
    {
     puts("ERRO CRIACAO PARAMETROS ");
     puts(VIDEO_arquivo_parametros_basicos);
     return(FALSE);
    }

 for (cont = 0;cont < 6;cont++,tam++)
      if (write(desc,tam,sizeof(INT2)) != sizeof(INT2))
         {
          puts("ERRO GRAVACAO DO ARQUIVO DE PARAMETROS ");
          puts(VIDEO_arquivo_parametros_basicos);
          close(desc);
          return(FALSE);
         }
 tam = &tot[1];

 for (cont = 0;cont < 5;cont++,tam++)
      if (write(desc,ptrparam[cont],*tam) != *tam)
         {
          puts("ERRO GRAVACAO DO ARQUIVO DE PARAMETROS ");
          puts(VIDEO_arquivo_parametros_basicos);
          close(desc);
          return(FALSE);
         }
 close(desc);
 return(TRUE);
}







e

         {
          puts("ERRO GRAVACAO DO ARQUIVO DE PARAMETROS ");
          puts(VIDEO_arquivo_parametros_basicos);
          close(desc);
          return(FALSE);
         }
 close(desc);
 return(TRUE);
}







