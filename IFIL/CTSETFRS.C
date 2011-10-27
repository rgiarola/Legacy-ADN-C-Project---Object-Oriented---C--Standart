/* ============================================================================
    CTREE_setfrs()  - Le um "set" de um registro apontado por uma chave.
                      Para   funcionamento  desta   funcao, so e'   necessario
                      determinar o numero do indice (soma-se 1 para o primeiro
                      indice,  2 para proximo,  e assim por diante,  no numero
                      do arquivo), e  inicializar os campos chaves que compoem
                      a chave deste.
    SETFRS()        - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      target para acesso.
    RETORNA         - Zero em operacao OK, se chave nao encontrada retorna valor
                      negativo, em outro caso, retorna ctree isam_err.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_setfrs( numero_indice, target, tamanho_considerar, modo_leitura)
INT2   numero_indice;
char *target;
INT2   tamanho_considerar,
      modo_leitura;
{
    IDE_ARQUIVOS *work_ifil;            /* Para localizacao do IDE_CHAVES.*/
    char          work_target[128],     /* Para manipulacao dos segmento chave.*/
                 *buffer_leitura,       /* Para armazenamento dos dados.*/
                 *buffer_dados;
    INT2           err,                  /* Manipulacao do codigo de erros.*/
                  real_indice,
                  numero_arquivo;       /* Numero ctree arquivo.*/


    /* <<<<<< Check de Parametros >>>>>*/
    if( numero_indice  < I(1) )
        return( I(-1) );

    if ( target == VD_NILL(char) )
        return( I(-2) );


    if( (real_indice=CTREE_tmpkey(numero_indice))<0)
      return(-3);

    /* Cosegue o ctree numero arquivo.*/
    if ( (numero_arquivo=CTREE_keyfil(numero_indice)) < 0 )
        return( I(-3) );


#ifdef CTREE_MULTI_USER         /* <<<<< Definicao Sistemas Multi-Usuarios >>>>.*/

    if (modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_ISAM;     /* Leitura para o buffer Isam.*/
    else
        ATIVA_BUF_EXTRA;    /* Leitura para o buffer Extra.*/

    if( (buffer_leitura = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-4) );

    /* Consegue o Buffer de Dados.*/
    ATIVA_BUF_DADOS;
    if( (buffer_dados = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-5) );

    /* Obtem estrutura de controle IDE_ARQUIVOS.*/
    if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
        return( I(-6) );

#else                           /* <<<<< Definicao Sistemas Mono-Usuarios >>>>.*/

    if (modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_DADOS;        /* Leitura para o buffer Isam.*/
    else
        ATIVA_BUF_EXTRA;        /* Leitura para o buffer Extra.*/

    /* Consegue o Buffer de Dados.*/
    if((buffer_leitura=CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-4) );

#endif



    /* Executa a Tranformacao do Segmento (apartir do protocolo IDE_CHAVES).*/
	if( DATABASE_TransformKey( real_indice, target ) == NULL )
        return( I(isam_err) );

	if( (err=DATABASE_FirstInSet( real_indice, target,
                         buffer_leitura,tamanho_considerar )) != 0 )
        {
            /* Registro nao localizado ou Falha do sistema C-tree.*/
            return( I(err) );
        }

#ifdef CTREE_MULTI_USER
    if ( modo_leitura ==  CT_LE_DADOS )
        VIDEO_movbloco( buffer_dados, buffer_leitura, work_ifil->dreclen );
#endif

 return(FALSE);

}


