/* ============================================================================
    CTREE_setlst()  - Le o ultimo "set" de um registro apontado por uma chave.
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

INT2   CTREE_setlst( numero_indice, target, tamanho_considerar, modo_leitura)
INT2   numero_indice;
char *target;
INT2   tamanho_considerar,
      modo_leitura;
{
    IDE_ARQUIVOS *work_ifil;            /* Para localizacao do IDE_CHAVES.*/
    char          work_target[128],     /* Para manipulacao dos segmento chave.*/
                 *buffer;               /* Para armazenamento dos dados.*/
    INT2           err,                  /* Manipulacao do codigo de erros.*/
                  real_indice,
                  numero_arquivo;       /* Numero ctree arquivo.*/


    /* <<<<<< Check de Parametros >>>>>*/
    if( numero_indice  < I(1) )
        {   /* Ctree numero do Indice fora de linha.*/
            return( I(-1) );
        }


    if ( target == VD_NILL(char) )
        return( I(-2) );

    if( (real_indice=CTREE_tmpkey(numero_indice))<0)
      return(-3);

    /* Cosegue o ctree numero arquivo.*/
    if ( (numero_arquivo=CTREE_keyfil( numero_indice )) < I(0) )
        return( I(-3) );

    if( modo_leitura == CT_LE_DADOS )
      ATIVA_BUF_DADOS;
    else
      ATIVA_BUF_EXTRA;

    if( (buffer = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        return( I(-4) );


    /* Executa a Tranformacao do Segmento (apartir do protocolo IDE_CHAVES).*/
	if( DATABASE_TransformKey( real_indice, target ) == NULL )
        return( I(isam_err) );


    if( (err=DATABASE_LastInSet( real_indice, target,
						 buffer, tamanho_considerar )) != 0 )
        {
            /* Registro nao localizado ou Falha do sistema C-tree.*/
            return( I(err) );
        }


 return(FALSE);
}


