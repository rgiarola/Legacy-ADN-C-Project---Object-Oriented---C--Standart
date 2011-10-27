/* ============================================================================
   CTREE_isopen()  - Cria e abre um arquivo.
                      Seu funcionamento e'semelhante ao das funcoes compativeis
                      ISAM.
                      Tipo HIBRIDA.
   Retorna:     Retorna zero se tudo OK, em erro retorna um nao valor zero
                (verifique variavel global "uerr_cod").
   ============================================================================ */
#include <INCVIDEO.H>


INT2 CTREE_openfile(arquivo,nome)
int  arquivo;
char *nome;
{
 CT_TMP_NOMES aux_tempor;
 IDE_ARQUIVOS auxifil;

 /* Consegue o do arquivo. ====================================================*/
 strcpy( aux_nome_arq, nome_dados );
 strcat( aux_nome_arq, ".");
 strcat( aux_nome_arq, ext_dados );

 strcpy(aux_tempor[0].temp_nome,nome);
 strcat(aux_tempor[0].temp_nome,".DAT");
 strcpy(aux_tempor[1].temp_nome,nome);
 strcat(aux_tempor[1].temp_nome,".IDX");


 dfilno = arquivo_ifil->dfilno;
 arquivo_ifil->dfilno = -1;

 vtclose();
 vtclose();
 if (especial_modo )                    /* ESPECIAL MODO->Tenta abrir primeiro.*/
    ret=CTREE_opentmp(arquivo_ifil,aux_tempor);


 vtclose();
 vtclose();
 if (!especial_modo || ret==FNOP_ERR)   /* Tenta CRIAR Arquivo.*/
    {
     ret=CTREE_criatmp( arquivo_ifil, aux_tempor);

     if (!ret)                          /* Criacao de Arquivo BEM SUCEDUDA ...*/
        {
         /* Finaliza OPERACAO OPEN/CRIA*/
         DATABASE_CloseIFile( arquivo_ifil );
         if ((ret=CTREE_opentmp(arquivo_ifil,aux_tempor))!=FALSE)
            {
             arquivo_ifil->dfilno = dfilno;
             return(ret);    /* FATAL ERRO!!! Retorna.*/
            }
        }
    }

 /* Se (criacao) && (open) falham tenta rebuild. ------------------------------*/
 if(  especial_modo   &&
     (ret == KOPN_ERR || ret == DOPN_ERR ||
      ret == FCRP_ERR || ret == FCMP_ERR || ret == INIX_ERR) )
   {
#ifndef CTREE_MULTI_USER
    if (especial_modo)
       if ( strcmp("DAT",ext_dados) || strcmp("IDX",ext_indice) )
          flag_rebuild = FALSE;

    if (flag_rebuild)
       {
        aux_rebuild1 = arquivo_ifil->pfilnam;
        strcpy ( aux_rebuild2, nome_dados );
        arquivo_ifil->pfilnam = aux_rebuild2;

        if ((ret=DATABASE_RebuildIFile(arquivo_ifil))!=FALSE)   /* Rebuild*/
           {
             arquivo_ifil->dfilno = dfilno;
             return( ret );
           }

        /*DATABASE_CloseIFile( arquivo_ifil );*/
        arquivo_ifil->pfilnam = aux_rebuild1;

        ret=CTREE_opentmp(arquivo_ifil,aux_tempor);     /* RE-ABRE O arquivo*/

       }
    else
       ret = -1;

     arquivo_ifil->dfilno = dfilno;

    if (ret)            /* FATAL ERRO!!! Retorna.*/
       return(ret);     
#else
         CTREE_erroreb_rede(dfilno);
         return(-1);
#endif
   }    // Fim de Rebuild Arquivo ...

 arquivo_ifil->dfilno = dfilno;

 /* ---------------------------------------------------------------------------
    Inicializa os Numero dos arquivos para referencia.
    --------------------------------------------------------------------------- */
 aux_tempor->numero_arquivo     = arquivo_ifil->dfilno;
 if (extra_posicao)
    (aux_tempor+1)->numero_arquivo = arquivo_ifil->dfilno+1;

 return(ret);

}

