/* ============================================================================
    CTREE_inbuf() - Dado o numero do arquivo, inicializa o buffer de dados
                    do mesmo.
    CTINBUF()     - Nome abreviado.
    PARAMETRO:  numero do arquivo.
    RETORNO:    zero quando OK, em erro retorna um valor negativo.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 CTREE_inbuf(numero_arquivo)
INT2 numero_arquivo;
{
    char *endereco_inicio_buffer;
    IDE_DODA     *work_doda;
    IDE_ARQUIVOS *work_ifil;



    if( (work_ifil = CTREE_ifilend( numero_arquivo )) == VD_NILL(IDE_ARQUIVOS) )
            return( I(-1) );
    else
            if ( (work_doda = CTREE_dodaend( work_ifil->rfstfld) )
                == VD_NILL(IDE_DODA) )
                /* Primeiro campo nao definido em doda.*/
                return( I(-2) );

    endereco_inicio_buffer = work_doda->fadr;

    /* Inicializa o buffer de dados.*/
    VIDEO_setmem(endereco_inicio_buffer, work_ifil->dreclen, 0);

 return( I(FALSE) );
}

