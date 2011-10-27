/* ============================================================================
    CTREE_lstrec()  - Dado o numero do arquivo ou indice, le o ultimo
                      registro deste.
                    OBS: A funcao insitira 3 (tres) vezes para conseguir o
                         ultimo registro, para evitar interferencias em
                         sistemas multi-usuarios.
    LSTREC()        - Nome abreviado.
    PARAMETRO:  Numero do ctree arquivo,
                modo de leitura de dados.
    RETORNA:    Zero se operacao ok, retorna isam_err em erro.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 CTREE_lstrec(numero_indice, modo_leitura)
INT2 numero_indice,
    modo_leitura;
{
    IDE_ARQUIVOS    *work_ifil;
    register INT2     err, count = 0;
    INT2              numero_arquivo,
                     real_indice;
    char            *buffer_dados,
                    *buffer_leitura;

    if ( (numero_arquivo=CTREE_keyfil(numero_indice)) < 0 )
        return( I(-1) );

    if( (real_indice=CTREE_tmpkey(numero_indice))<0)
      return(-2);

#ifdef CTREE_MULTI_USER         /* <<<<< Definicao Sistemas Multi-Usuarios >>>>.*/

    if (modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_ISAM;     /* Leitura para o buffer Isam.*/
    else
        ATIVA_BUF_EXTRA;    /* Leitura para o buffer Extra.*/


    if( (buffer_leitura = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        {
            return( I(-2) );
        }


    /* Consegue o Buffer de Dados.*/
    ATIVA_BUF_DADOS;
    if( (buffer_dados = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        {
            return( I(-3) );
        }

    /* Obtem estrutura de controle IDE_ARQUIVOS.*/
    if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
        {
            return( I(-4) );
        }

#else                           /* <<<<< Definicao Sistemas Mono-Usuarios >>>>.*/

    if (modo_leitura == CT_LE_DADOS)
        ATIVA_BUF_DADOS;        /* Leitura para o buffer de Dados.*/
    else
        ATIVA_BUF_EXTRA;        /* Leitura para o buffer Extra.*/

    /* Consegue o Buffer de Leitura.*/
    if((buffer_leitura=CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
        {
            return( I(-1) );
        }

#endif

    /* A funcao insistira tres vezes para conseguir o primeiro registro.*/
    do
        {
			err=DATABASE_LastRecord( real_indice, buffer_leitura );
            if ( count > 3 )
                return( I(err) );
            ++count;

        }   while ( err>0 );

#ifdef CTREE_MULTI_USER
    if ( modo_leitura == CT_LE_DADOS )
        VIDEO_movbloco( buffer_dados, buffer_leitura, work_ifil->dreclen );
#endif

    return( I(FALSE) );

}



