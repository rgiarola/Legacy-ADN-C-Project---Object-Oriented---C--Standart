/* ============================================================================
    CTREE_setprv()  - Le o anterior "set" de um registro apontado por uma chave.
                      Para   funcionamento  desta   funcao, so e'   necessario
                      determinar o numero do indice (soma-se 1 para o primeiro
                      indice,  2 para proximo,  e assim por diante,  no numero
                      do arquivo), e  inicializar os campos chaves que compoem
                      a chave deste.
    SETNXT()        - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      modo_leitura.
    RETORNA         - Zero em operacao OK, se chave nao encontrada retorna valor
                      negativo, em outro caso, retorna ctree isam_err.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_setprv( numero_indice, modo_leitura)
INT2   numero_indice;
INT2   modo_leitura;
{
    IDE_ARQUIVOS *work_ifil;            /* Para localizacao do IDE_CHAVES.*/
    char         *buffer;               /* Para armazenamento dos dados.*/
    INT2           numero_arquivo,       /* Numero ctree arquivo.*/
                  real_indice,err;

    /* <<<<<< Check de Parametros >>>>>*/
    if( numero_indice  < I(1) )
        {   /* Ctree numero do Indice fora de linha.*/
            return( I(-1) );
        }

         
    /* Cosegue o ctree numero arquivo.*/
    if ( (numero_arquivo=CTREE_keyfil( numero_indice )) < I(0) )
        return( I(-2) );

    if( (real_indice=CTREE_tmpkey(numero_indice))<0)
      return(-3);

    if( modo_leitura == CT_LE_DADOS )
      ATIVA_BUF_DADOS;
    else
      ATIVA_BUF_EXTRA;

    if( (buffer = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-3) );

    if( (err=DATABASE_PreviousInSet( real_indice, buffer)) != FALSE )
        {
            /* Registro nao localizado ou Falha do sistema C-tree.*/
            return( I(err) );
        }

  return(FALSE);
}


