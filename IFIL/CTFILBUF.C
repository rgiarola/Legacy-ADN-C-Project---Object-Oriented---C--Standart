/* ============================================================================
   CTREE_filbuf() - Dado o numero ctree do arquivo consegue o endereco inicial
                    do buffer do arquivo de dados.
    CTFILBUF()    - Nome abreviado.
    PARAMETRO     - Numero do arquivo.
    RETORNA       - Endereco inicial do buffer de dados, em erro, retorna null.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 ATUAL_NO_BUFFER = 0;

char *CTREE_filbuf(numero_arquivo)
INT2  numero_arquivo;
{
 char             *retorno_buffer;
 IDE_TABREFERDODA *elemento;

 if (numero_arquivo < 0)
     return( VD_NILL(char) );

 if (numero_arquivo >= (VIDEO_bufparamarq->numarq+VIDEO_bufparamarq->numind))
     return( VD_NILL(char) );

 elemento = (VIDEO_bufparamarq->bufdodas+numero_arquivo);

 if (elemento->numero != numero_arquivo)
     return( VD_NILL(char) );
 
 retorno_buffer = elemento->buffer;

    /* O ponteiro retornado sera igual a area a qual se esta trabalhando
       determinado por "ATUAL_NO_BUFFER" (buffer primario ou extendido),
       calculado pela extensao do mesmo.                                    */

 return(retorno_buffer+(ATUAL_NO_BUFFER*(elemento->tamanho)));
}

