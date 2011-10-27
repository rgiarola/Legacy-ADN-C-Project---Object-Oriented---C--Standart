/* ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³   COPIA DADOS ENTRE ARQUIVOS SEMELHANTES.                                ³
   ³   Dado uma chave, esta funcao executa copia de dados entre origem e      ³
   ³   destino, lendo do buffer extra para o buffer de dados e gravando.      ³
   ³                                                                          ³
   ³   PARAMETROS:                                                            ³
   ³   indice_destino  -> numero do indice onde serem lido os dados.          ³
   ³   indice_origem   -> numero do indice onde serao trasferidos os dados.   ³
   ³   chave           -> protocolo extendido de controle de chaves.          ³
   ³   modo_oper       -> modo de operacao                                    ³
   ³                      0-AddRec 1-ReWrite com verificacao de existencia.   ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ */
#include <INCVIDEO.H>


INT2   CTREE_copy(  indice_destino, indice_origem, chave, modo_oper, user_func)
INT2                indice_destino,
                   indice_origem;
VIDEO_SEG_CHAVE   *chave;
INT2                modo_oper,
                 (*user_func)();  /* Funcao Generica.*/
{
 VIDEO_SEG_CHAVE  *user_chave;
 IDE_ARQUIVOS     *ifil_origem,      /* Ponteriro para estruturas CONTROLE IFIL.*/
                  *ifil_destino;
 INT2               ret,              /* Variavel aux. para trat. erros.*/
                   ret_func,         /* Variavel aux. para "user_func".*/
                   flag_buf_copia,   /* Flag para se eftuar copia de buffer's.*/
                   arquivo_origem,   /* Numero ctree do arquivo origem.*/
                   arquivo_destino,  /* Numero ctree do arquivo destino.*/
                   tmpfil;           /* Tmp file                        */
 char             *buffer_origem,    /* Buffer de dados origem.*/
                  *buffer_destino,   /* Buffer de dados destino.*/
                  *buffer_processo,
                  *buffer_antes   =VD_NULO;
 BOOLEAN          flagregistro;


 if( indice_destino<1 || indice_origem<1)
     return(-1);

 if (((arquivo_destino=CTREE_keyfil( indice_destino )) < 0) ||
     ((arquivo_origem= CTREE_keyfil( indice_origem  )) < 0))
    return(-3);

 /* ============================================
    Consegue o buffer de dados.
    ============================================ */
 ATIVA_BUF_DADOS;
 if( (buffer_origem= CTREE_filbuf(arquivo_origem)) == VD_NILL(char) )
     return( I(-4) );

 ATIVA_BUF_DADOS;
 if( (buffer_destino= CTREE_filbuf(arquivo_destino)) == VD_NILL(char) )
     return( I(-5) );

 if( ((ifil_origem= CTREE_ifilend(arquivo_origem ))==VD_NILL(IDE_ARQUIVOS))||
     ((ifil_destino=CTREE_ifilend(arquivo_destino))==VD_NILL(IDE_ARQUIVOS)) )
  return(-6);

 if((flagregistro = (buffer_origem == buffer_destino)) == TRUE)
   {               
    flag_buf_copia=FALSE;
   }
 else
   flag_buf_copia=TRUE;

 // Salva Posicao do Arquivo origem
 buffer_antes  =CTREE_pusharq( arquivo_origem );

// VD_gtxy(1,1); printf ("
 if ( (ret=CTREE_find( indice_origem, chave,
                       FIND_PRIMEIRO, CT_LE_EXTRA_REPASSA ))!=0)
    {
     CTREE_poparq( arquivo_origem, buffer_antes );
     return(ret);
    }


 /* ============================================
    LOOP para copy de informacoes
    ============================================ */
 ret_func= ret =0;

 do
   {
    /* =============================================
       pega a posicao corrente do registro
    ============================================= */
    if (flagregistro)
       {
        buffer_processo = CTREE_pusharq (arquivo_origem);

        if (!CTREE_pusharqtest(buffer_processo))
           {
            CTREE_poparq( arquivo_origem, buffer_antes );
            return(isam_err);
           }
       }

    /* =============================================
       Controle de retorno da funcao:
       == 0 -> Processamento normal.
       >  0 -> Nao processa este registro.
       <  0 -> Nao faz copia sobre o buffer de dados.
       ============================================= */
    if( user_func )
      ret_func = (*user_func)( flag_buf_copia, arquivo_origem, arquivo_destino );

    if( flag_buf_copia && !ret_func)
        VIDEO_movbloco( buffer_destino, buffer_origem,
                min(ifil_origem->dreclen,ifil_destino->dreclen) );

    if(ret_func<=0)
      {
       if(modo_oper==0)
        {
         if( (ret=CTREE_adrec( arquivo_destino ))!=0)
             {
              char buffer[200];
              sprintf(buffer,CTREE_MENS_mens_padrao_err,
                             CTREE_MENS_err_addrec_ctcopy,
                             (VIDEO_bufparamarq->bufdodas+arquivo_destino)->reduzido,
                             ret,isam_err);
              VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_add_rec_ctcopy);
              CTREE_poparq( arquivo_origem, buffer_antes );
              return(ret);
             }

         if (flagregistro)
              flagregistro |= BIT1;
        }
      else
        {
         if( (ret=CTREE_rewrec( arquivo_destino ))!=0)
             {
              char buffer[200];
              sprintf(buffer,CTREE_MENS_mens_padrao_err,
                             CTREE_MENS_err_addrec_ctcopy,
                             (VIDEO_bufparamarq->bufdodas+arquivo_destino)->reduzido,
                             ret,isam_err);
              VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_rew_rec_ctcopy);
              CTREE_poparq( arquivo_origem, buffer_antes );
              return(ret);
             }

         if (flagregistro)
              flagregistro |= BIT1;
        }
      }

    /* =========================================
       Le o proximo registro da lista
       ========================================= */

    if (flagregistro&BIT1)
       {
        CTREE_poparq( arquivo_origem, buffer_processo );
        if (!CTREE_pusharqtest(buffer_processo))
           {
            CTREE_poparq( arquivo_origem, buffer_antes );
            return(isam_err);
           }
        flagregistro &= (~BIT1);
       }
     else
       if (flagregistro)
          {
           VIDEO_FREE_ALLOC_MEM(buffer_processo);
          }

    ret = CTREE_find( indice_origem, chave,FIND_PROXIMO, CT_LE_EXTRA_REPASSA);

   }while( !ret ); /* Fim de LOOP.*/

 CTREE_poparq( arquivo_origem, buffer_antes );

 return(ret);
}

