/* ============================================================================
   CTREE_ifilend() - Dado o numero do arquivo consegue um ponteiro para a
                     estrutura IFIL.
   IFILEND()       - Nome abreviado.
   PARAMETRO: Numero do arquivo.
   RETORNA:   Ponteiro para estrutura IFIL, em erro, retorna NULL.
   ============================================================================ */
#include <INCVIDEO.H>

IDE_ARQUIVOS *CTREE_ifilend(numero_arquivo)
INT2 numero_arquivo;
{
 IDE_TABREFERDODA *elemento;
 IDE_ARQUIVOS     *auxifil;

 if (numero_arquivo < 0)
     return( VD_NILL(IDE_ARQUIVOS) );

 if (numero_arquivo >= (VIDEO_bufparamarq->numarq+VIDEO_bufparamarq->numind))
     return( VD_NILL(IDE_ARQUIVOS) );

 elemento = (VIDEO_bufparamarq->bufdodas+numero_arquivo);

 if (elemento->numero != numero_arquivo)
     return( VD_NILL(IDE_ARQUIVOS) );
 
 auxifil = VIDEO_bufparamarq->arquivos+
           (VIDEO_bufparamarq->bufdodas+numero_arquivo)->postab;

 if (auxifil->dfilno != numero_arquivo)
     return( VD_NILL(IDE_ARQUIVOS) );

 return(VIDEO_bufparamarq->arquivos+
        (VIDEO_bufparamarq->bufdodas+numero_arquivo)->postab);
}

