/* ============================================================================
    CTREE_rewrec()  -   Atualiza um dado registro de um arquivo.
                        OBS: Esta funcao usa o protocolo de verificacao de
                             interferencias de sistemas multi-usuarios, com
                             comparacao dos dados.
    PARAMETRO:          Numero Ctree do arquivo de dados.
    RETORNA:            Zero se protocolo de atualizacao bem sucedido,
                        caso contrario, um nao valor zero.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 CTREE_rewrec(numero_arquivo)
INT2 numero_arquivo;
{
    IDE_ARQUIVOS *work_ifil;
    INT2   err, real_arquivo;
    char *buffer_dados,     /* Ponteiro regiao de dados a se atualizar.*/
         *buffer_isam,      /* Ponteiro regiao de check de dados.*/
         *buffer_extra;     /* Ponteiro regiao do corrente isam record.*/

    if( (real_arquivo=CTREE_tmpfil(numero_arquivo))<0)
     return(-1);


#ifdef CTREE_MULTI_USER     /* Protocolo Multi-Usuario para Gravacao.*/
    /* Consegue o buffer do current isam record.*/
    ATIVA_BUF_ISAM;
    if( (buffer_isam = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-2) );

    /* Consegue o buffer extra para check dos dados.*/
    ATIVA_BUF_EXTRA;
    if( (buffer_extra = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-3) );


    /* Consegue o look para gravacao.*/


 if (_log_lock)
    if ( DATABASE_LockISAM(DATABASE_ENABLE) )
       return( I(isam_err) );

    /* Re-le o registro.*/
 if( (err=DATABASE_ReReadRecord(real_arquivo,buffer_extra))!=0 )
     {
      if (_log_lock)
         DATABASE_LockISAM(DATABASE_FREE);
      return( I(err) );
     }

 if( (work_ifil = CTREE_ifilend( numero_arquivo )) == VD_NILL(IDE_ARQUIVOS) )
   {
    if (_log_lock)
       DATABASE_LockISAM(DATABASE_FREE);
    return( I(-4) );
   }


    /* Compara Dados armazenados para verificacao se houve atualizacao de dados.*/
    if (memcmp( buffer_isam, buffer_extra, work_ifil->dreclen ) )
       {
        char buffer[200];

        if (_log_lock)
           DATABASE_LockISAM(DATABASE_FREE);

        sprintf(buffer,CTREE_MENS_mens_padrao_err,
                       CTREE_MENS_err_reg_rede,
                       (VIDEO_bufparamarq->bufdodas+numero_arquivo)->reduzido,
                       1,isam_err);
        VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_reg_red_alterado);
        return ( I(-5) );
       }

#else

    /* Consegue Lock de Gravacao.*/
 if (_log_lock)
    if ( DATABASE_LockISAM(DATABASE_ENABLE) )
       return( I(isam_err) );

#endif


    /* Consegue o buffer de dados.*/
    ATIVA_BUF_DADOS;

    if( (buffer_dados = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
      {
       if (_log_lock)
          DATABASE_LockISAM(DATABASE_FREE);
       return( I(-1) );
      }



   if( (err=DATABASE_ReWriteRecord(real_arquivo,buffer_dados))!=0 )
     {
      if (_log_lock)
         DATABASE_LockISAM(DATABASE_FREE);
      return (err);
     }

 if (_log_lock)
    if ((err=DATABASE_LockISAM(DATABASE_FREE))!=FALSE)
       return (err);

 if (!_log_disable)
    {
     strcpy (_log_oper,"ALTERA");
     CTREE_adlog(numero_arquivo);
    }


#ifdef CTREE_MULTI_USER     /* Protocolo Multi-Usuario para Gravacao.*/
  VIDEO_movbloco(buffer_isam,buffer_dados, work_ifil->dreclen );
#endif

 return(FALSE);
}

