/* ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³   EXCLUI DADO DE UM ARQUIVO.                                             ³
   ³   Dado uma chave, esta funcao excluira todos os dados semelhantes.       ³
   ³                                                                          ³
   ³   PARAMETROS:                                                            ³
   ³   indice_busca    -> numero do indice de busca.                          ³
   ³   chave           -> protocolo extendido de controle de chaves.          ³
   ³   user_func       -> user func de controle de exclusao.                  ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ */
#include <INCVIDEO.H>


INT2   CTREE_dlall( indice_busca, chave, user_func)
INT2                indice_busca;
VIDEO_SEG_CHAVE   *chave;
INT2              (*user_func)();  /* Funcao Generica.*/
{
 INT2               ret,              /* Variavel aux. para trat. erros.*/
                   ret_func,         /* Variavel aux. para "user_func".*/
                   arquivo_busca;    /* Numero ctree do arquivo destino.*/

 if( indice_busca<0 )
     return(-1);

 if ( (ret=CTREE_find( indice_busca, chave,
                       FIND_PRIMEIRO, CT_LE_EXTRA_REPASSA ))!=0)
    return(ret);

 if ( (arquivo_busca=CTREE_keyfil( indice_busca ))<0)
    return(-3);

 /* ============================================
    LOOP para Exclusao de informacoes
    ============================================ */
 ret_func= ret =0;
 while( !ret )
   {

    /* =============================================
       Controle de retorno da funcao:
       == FALSE -> Processamento normal.
       == TRUE  -> Nao processa este registro.
       ============================================= */
    if ( user_func )
       ret_func = (*user_func)( arquivo_busca );

    if ( !ret_func )
       if ((ret=CTREE_dlrec( arquivo_busca ))!=0)
          return(-4);

    /* =========================================
       Le o proximo registro da lista
       ========================================= */
    ret = CTREE_find( indice_busca, chave,FIND_PROXIMO, CT_LE_EXTRA_REPASSA);

   } /* Fim de LOOP.*/

 return(ret);
}

