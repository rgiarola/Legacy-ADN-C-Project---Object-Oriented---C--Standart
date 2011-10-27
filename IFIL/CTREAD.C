/* ============================================================================
    CTREE_readrec() - Le o registro de determinado indice, por determinada
                      chave.
                      Para   funcionamento  desta   funcao, so e'   necessario
                      determinar o numero do indice (soma-se 1 para o primeiro
                      indice,  2 para proximo,  e assim por diante,  no numero
                      do arquivo), e  inicializar os campos chaves que compoem
                      a chave deste.
    READREC()       - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      target para acesso,
                      modo de operacao.
                      OBS: O modo de operacao e'usado para especificar em que
                           buffer estarao os dados. Em sistemas multi-usuarios,
                           no minimo tres buffer's, em mono-usuario, no minimo
                           dois buffer's.
    RETORNA         - Zero se operacao OK, se chave nao encontrada retorna valor
                      negativo, em outro caso, retorna ctree isam_err.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_readrec( numero_indice, target, modo_leitura )
INT2   numero_indice;
char *target;
INT2   modo_leitura;
{
    IDE_ARQUIVOS *work_ifil;            /* Para localizacao do IDE_CHAVES.*/
    IDE_INDEX    *work_index;
    IDE_CHAVES   *work_chaves;
    char          work_target[128],     /* Para manipulacao dos segmento chave.*/
                 *buffer_leitura,       /* Pont. buffer de armazenagem primaria.*/
                 *buffer_dados;         /* Pont. buffer para os atuais dados.*/
    INT2           flag_duplicata,       /* Flag para duplicata.*/
                  numero_segmentos,     /* Numero Segmentos para formar a chave.*/
                  tamanho_chave,        /* Tamanho da Chave.*/
                  posicao_target,       /* Marca a posicao de concatenacao.*/
                  err,                  /* Manipulacao do codigo de erros.*/
                  numero_arquivo,       /* Numero ctree arquivo.*/
                  real_indice,
                  desc;

    /* <<<<<< Check de Parametros >>>>>*/
    if( numero_indice  < 0 )
        return( I(-1) );

    /* Cosegue o numeros ctree do indice*/
    if( (numero_arquivo=CTREE_keyfil(numero_indice)) < 0 )
        return( I(-2) );

    if( (real_indice=CTREE_tmpkey(numero_indice))<0)
       return(-3);


#ifdef CTREE_MULTI_USER     /* Protocolo de Atualizacao de dados (Multi-Usuario).*/

    /* Consegue o buffer de Leitura.*/
    if ( modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_ISAM;
    else
        ATIVA_BUF_EXTRA;


    if( (buffer_leitura = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-3) );

    ATIVA_BUF_DADOS;
    if( (buffer_dados   = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-4) );


#else                       /* Protocolo de Atualizacao de Dados (Mono-Usuario).*/

    /* Consegue o buffer de Leitura.*/
    if ( modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_DADOS;    /* Nao usa o buffer isam.*/
    else
        ATIVA_BUF_EXTRA;


    if( (buffer_leitura=CTREE_filbuf(numero_arquivo))==VD_NILL(char) )
        return( I(-3) );

#endif

    /* Obtem estrutura de controle IDE_ARQUIVOS.*/
    if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
        return( I(-4) );


    /* Seta o ponteiro para indice (IDE_CHAVES) em uso.*/
    work_index = (work_ifil->ix + (numero_indice-numero_arquivo-1));

    /* Verifica se Arquivo permite duplicatas.*/
    if( (flag_duplicata=(work_index->ikeydup)) == TRUE )
        {
            tamanho_chave = ((work_index->ikeylen) - sizeof(long));
        }



    /*  ==================================================
        A chave sera montada apartir do buffer de dados
        (protocolo IDE_CHAVES), se nenhuma foi declarada.
        ================================================== */
    if (target == VD_NULO )
       {
        if( (err=CTREE_getchave( numero_indice, work_target, BUFFER_DADOS ))!=0)
          return( I(-5) );
        target = work_target;   /* Seta o Target.*/
       }

    /* Executa a Tranformacao do Segmento (apartir do protocolo IDE_CHAVES).*/
    if ((target = DATABASE_TransformKey( real_indice, target ))==VD_NULO)
       return(isam_err);

    /*  ------------------------------------------------------------------
        Se duplicatas sao permitidas, GetRecord() nao conseguira localizar
        o registro, necessitando da funcao FirstInSet().
        ------------------------------------------------------------------  */
    if( !flag_duplicata )
      err=DATABASE_GetRecord( real_indice, target, buffer_leitura );
    else
     err=DATABASE_FirstInSet( real_indice,target, buffer_leitura,tamanho_chave);


    if (err)
        {
            /* Registro nao localizado ou Falha do sistema C-tree.*/
            return( I(err) );
        }

#ifdef CTREE_MULTI_USER
    /* Mapeia do buffer isam, para o buffer de dados.*/
    if( modo_leitura == CT_LE_DADOS)
        VIDEO_movbloco( buffer_dados, buffer_leitura, work_ifil->dreclen);
#endif

    return( I(FALSE) );

}

