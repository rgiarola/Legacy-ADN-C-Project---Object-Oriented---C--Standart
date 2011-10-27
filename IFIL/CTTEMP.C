/* ============================================================================
   CTREE_opentmp()  - Cria e abre um arquivo temporario.
                      Seu funcionamento e'semelhante ao das funcoes compativeis
                      ISAM.
                      Tipo LOW_LEVEL.
   Retorna:     Retorna zero se tudo OK, em erro retorna um nao valor zero
                (verifique variavel global "uerr_cod").
   ============================================================================ */
#include <INCVIDEO.H>


INT2 CTREE_temp(arquivo_ifil)
IDE_ARQUIVOS     *arquivo_ifil;
{
 CT_TMP_NOMES *aux_tempor;      /* Controle Arquivos Temporarios.*/
 IDE_ARQUIVOS auxifil;
 char         aux_nome_arq[VD_MAX_TMP_NOME];
 INT2          ret,
              extra_posicao,
              pos_nome_arq;

 if (arquivo_ifil->dnumidx>0)
    extra_posicao = TRUE;
 else
    extra_posicao = FALSE;

 aux_tempor    = CT_arquivos_temporarios;
 pos_nome_arq  = 0;

 /* Encontra a Primeira posicao avaliavel.*/
 while (pos_nome_arq < (VD_MAX_TMP-extra_posicao) )
  {
   if (!aux_tempor->temp_nome[0])
      {
       if (extra_posicao)
          {
           if( (aux_tempor+1)->temp_nome[0] )
             {
              VIDEO_mostra_mens_erro(CTREE_mens_cttemp,
                                     VIDEO_ERRO_posicao_seguinte_cttemp);
              ++aux_tempor;
              ++pos_nome_arq;
              continue;
             }
          }
        break;
      }
   ++pos_nome_arq;
   ++aux_tempor;
  }

 if( pos_nome_arq >= (VD_MAX_TMP-extra_posicao) )   /* Nao ha espaco para arquivos temporarios.*/
    return( -1 );

 vtclose();
 vtclose();
 /* Consegue os nome a serem usados como temporarios.*/
 DATABASE_GetTempFileName( aux_nome_arq, VD_MAX_TMP_NOME );
 strcpy( aux_tempor->temp_nome, aux_nome_arq );

 if (extra_posicao)
    {
     DATABASE_GetTempFileName( aux_nome_arq, VD_MAX_TMP_NOME );
     strcpy( (aux_tempor+1)->temp_nome, aux_nome_arq );
    }


 if ((ret=DATABASE_criatmp( arquivo_ifil, aux_tempor))!=0 )
    {
     char buffer[200];
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    CTREE_mens_cttemp_cria,
                    (VIDEO_bufparamarq->bufdodas+arquivo_ifil->dfilno)->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_cria_tmp_cttemp);
     if (extra_posicao)
        (aux_tempor+1)->temp_nome[0] = 0;
     aux_tempor->temp_nome[0] = 0;
     return(-2);
    }

 DATABASE_CloseIFile( arquivo_ifil );

 if ((ret=DATABASE_opentmp(arquivo_ifil, aux_tempor))!=0 )
    {
     char buffer[200];
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    CTREE_mens_cttemp_open,
                    (VIDEO_bufparamarq->bufdodas+arquivo_ifil->dfilno)->reduzido,
                    ret,isam_err);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_open_tmp_cttemp);
     if (extra_posicao)
        (aux_tempor+1)->temp_nome[0] = 0;
     aux_tempor->temp_nome[0] = 0;
     return(-3);
    }

 /* ========================================================
    Inicializa os Numero dos arquivos para referenciacao.
    ======================================================== */
 aux_tempor->numero_arquivo     = arquivo_ifil->dfilno;
 (aux_tempor+1)->numero_arquivo = arquivo_ifil->dfilno+1;

 return(ret);

}

