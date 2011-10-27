#include <INCVIDEO.H>

INT2 VIDEO_carga_parametros(VD_VOID)
{
 INT2      desc,
          cont1,
          cont2,
          *tam;
 long int tamarq;
 BYTE     *ptraux;

#if defined(__VIDEO_CARGA_PARAMETROS__)
 VD_VOID **ptrparam[] = {(VD_VOID *) &VIDEO_box_parametros,
                         (VD_VOID *) &VIDEO_dim_tela_parametros,
                         (VD_VOID *) &VIDEO_ADMEM_parametros,
                         (VD_VOID *) &VIDEO_tcl_filtro_parametros,
                         (VD_VOID *) &VIDEO_adm_window_parametros};

  if ((desc = VD_open_ler(VIDEO_arquivo_parametros_basicos)) < 0)
    {
     puts("ERRO NA ABERTURA DE ARQUIVO DE PARAMETROS BASICOS\n");
     puts(VIDEO_arquivo_parametros_basicos);
     return(FALSE);
    }
 if ((tamarq = filelength(desc)) <= 0L)
    {
     puts("ERRO NO TAMANHO DO ARQUIVO DE PARAMETROS BASICOS\n");
     return(FALSE);
    }

 if ((VIDEO_buffer_parametros_basicos = (BYTE *)
    VIDEO_alloc_parametros(W(tamarq))) == VD_NULO)
    {
     puts("ERRO ALOCACAO DE MEMORIA DE PARAMETROS BASICOS\n");
     return(FALSE);
    }

 tam    = (INT2 *) VIDEO_buffer_parametros_basicos;
 ptraux = (BYTE *) VIDEO_buffer_parametros_basicos;

 if ((read(desc,ptraux,W(tamarq)) < W(tamarq)) ||
     (*tam != W(tamarq)))
    {
     puts("ERRO NA CARGA DO ARQUIVO DE PARAMETROS BASICOS\n");
     printf("BUFFER %d TAMARQ %d",W(*tam),W(tamarq));
     VIDEO_free_alloc_parametros(ptraux);
     return(FALSE);
    }

 ptraux += (sizeof(INT2) * 6);

 for (cont1 = 0;cont1 < 5;cont1++)
     {
      ++tam;
      *ptrparam[cont1] = ptraux;
      ptraux += *tam;
     }
 close(desc);

/*=========================================================================*/

 if ((VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer =
      VIDEO_alloc_parametros(VIDEO_ADMEM_parametros->VIDEO_ADMEM_tam_area))
      == VIDEO_NULO)
    {
     VIDEO_free_alloc_parametros(VIDEO_buffer_parametros_basicos);
     return(FALSE);
    }

 VIDEO_ADMEM_parametros->VIDEO_ADMEM_topo =
                           VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer +
                           VIDEO_ADMEM_parametros->VIDEO_ADMEM_tam_area - 1;
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_base =
                           VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer +
                          (VIDEO_ADMEM_parametros->VIDEO_ADMEM_num_descmem *
                           sizeof(VIDEO_ADMEM_DESCRITOR));
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_mem = PTR_CAST(VIDEO_ADMEM_DESCRITOR,
 VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer);

/*=========================================================================*/

 if ((VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl =
      VIDEO_alloc_parametros(VIDEO_TAMBUFTCL))
     == VIDEO_NULO)
    {
     VIDEO_free_alloc_parametros(
                 VIDEO_ADMEM_parametros->VIDEO_ADMEM_area_buffer);
     VIDEO_free_alloc_parametros(VIDEO_buffer_parametros_basicos);
     return(FALSE);
    }

 VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbufini =
 VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl,
 VIDEO_tcl_filtro_parametros->VIDEO_filtro_tclbuffin =
 VIDEO_tcl_filtro_parametros->VIDEO_filtro_buffertcl,

/*=========================================================================*/

 VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win =
 VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win_buffer;
     
 VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win_fim =
 VIDEO_adm_window_parametros->VIDEO_pilha_desc_disp_win_buffer + 199;
     
 VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_win =
 VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_win_buffer;

/*=========================================================================*/

#else

/*=========================================================================*/

 if ((VIDEO_ADMEM_area_buffer = VIDEO_alloc_parametros(VIDEO_ADMEM_tam_area))
     == VIDEO_NULO)
    return(FALSE);
 VIDEO_ADMEM_topo = VIDEO_ADMEM_area_buffer + VIDEO_ADMEM_tam_area - 1;
 VIDEO_ADMEM_base = VIDEO_ADMEM_area_buffer + (VIDEO_ADMEM_num_descmem *
                                            sizeof(VIDEO_ADMEM_DESCRITOR));
 VIDEO_ADMEM_area_mem =
             PTR_CAST(VIDEO_ADMEM_DESCRITOR,VIDEO_ADMEM_area_buffer);

/*=========================================================================*/

 if ((VIDEO_filtro_buffertcl = VIDEO_alloc_parametros(VIDEO_TAMBUFTCL))
     == VIDEO_NULO)
    {
     VIDEO_free_alloc_parametros(VIDEO_ADMEM_area_buffer);
     return(FALSE);
    }

 VIDEO_filtro_tclbufini = VIDEO_filtro_buffertcl,
 VIDEO_filtro_tclbuffin = VIDEO_filtro_buffertcl,

/*=========================================================================*/

 VIDEO_pilha_desc_disp_win = VIDEO_pilha_desc_disp_win_buffer;
     
 VIDEO_pilha_desc_disp_win_fim = VIDEO_pilha_desc_disp_win_buffer + 199;
     
 VIDEO_pilha_descritor_usado_win = VIDEO_pilha_descritor_usado_win_buffer;

/*=========================================================================*/

#endif

 return(TRUE);
}

