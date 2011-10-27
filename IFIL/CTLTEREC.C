/* ============================================================================
    CTREE_lterec()  - Le o registro de determinado indice, menor ou igual a
                      um target.
                      Para   funcionamento  desta   funcao, so e'   necessario
                      determinar o numero do indice (soma-se 1 para o primeiro
                      indice,  2 para proximo,  e assim por diante,  no numero
                      do arquivo), e  inicializar os campos chaves que compoem
                      a chave deste.
    LTREAD()        - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      target para acesso.
    RETORNA         - Zero em operacao OK, se erro de operacao retorna valor
                      em outro caso retorna ctree erro.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_lterec( numero_indice, target, modo_leitura )
INT2   numero_indice;
char *target;
{
    IDE_ARQUIVOS *work_ifil;            /* Para localizacao do IDE_CHAVES.*/
    char          work_target[128],     /* Para manipulacao dos segmento chave.*/
                 *buffer_leitura,       /* Pont. buffer de armazenagem primaria.*/
                 *buffer_dados;         /* Pont. buffer para os atuais dados.*/
    INT2           err,                  /* Manipulacao do codigo de erros.*/
                  real_indice,
                  numero_arquivo;       /* Numero ctree arquivo.*/


    /* <<<<<< Check de Parametros >>>>>*/
    if( numero_indice  < I(1) )
     {   /* Ctree numero do Indice fora de linha.*/
      return( I(-1) );
     }


    /* Cosegue o ctree numero arquivo.*/
    if( (numero_arquivo=CTREE_keyfil( numero_indice )) < 0 )
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

    /* Obtem estrutura de controle IDE_ARQUIVOS.*/
    if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
        return( I(-5) );

#else                       /* Protocolo de Atualizacao de Dados (Mono-Usuario).*/


    /* Consegue o buffer de Leitura.*/
    if ( modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_DADOS;    /* Nao usa o buffer isam.*/
    else
        ATIVA_BUF_EXTRA;


    if( (buffer_leitura=CTREE_filbuf(numero_arquivo))==VD_NILL(char) )
        return( I(-4) );

    buffer_dados = buffer_leitura;

#endif

    /*  ==================================================
        A chave sera montada apartir do buffer de dados
        (protocolo IDE_CHAVES), se nenhuma foi declarada.
        ================================================== */
    if ( target == VD_NILL(char) )
     {
      if( (err=CTREE_getchave( numero_indice, work_target, BUFFER_DADOS ))!=0)
        return( I(-5) );
      target = work_target;   /* Seta o Target.*/
     }


    /* Executa a Tranformacao do Segmento (apartir do protocolo IDE_CHAVES).*/
	if( DATABASE_TransformKey( real_indice, target ) == NULL)
      return( I(isam_err) );


	if( (err=DATABASE_GetLTERecord( real_indice, target, buffer_leitura)) != 0 )
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


