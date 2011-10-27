/* ============================================================================
   CTREE_tmpfil() - Dado o temporario numero de arquivo ctree, consegue o
                    numero do arquivo principal.
   CTFILKEY()     - Nome abreviado.
   PARAMETRO:       Temporario Numero do Arquivo Ctree.
   RETORNA:         O ctree numero do arquivo, em erro retorna um numero
                    negativo.
   ============================================================================ */
#include <INCVIDEO.H>

INT2  CTREE_tmpfil( tempo_numero )
INT2  tempo_numero;
{
 IDE_ARQUIVOS     *auxifil;
 IDE_TABREFERDODA *elemento;

 if (tempo_numero < 0)
    return(I(-1));

 if (tempo_numero >= (VIDEO_bufparamarq->numarq+
                      VIDEO_bufparamarq->numind))
     return( I(-3) );           /* Numero do Arquivo nao encontrado.*/

 elemento = (VIDEO_bufparamarq->bufdodas+tempo_numero);

 if (elemento->numero != tempo_numero)
     return( I(-3) );           /* Numero do Arquivo nao encontrado.*/
 
 auxifil = (VIDEO_bufparamarq->arquivos+
           (VIDEO_bufparamarq->bufdodas+tempo_numero)->postab);

 if (auxifil->dfilno != tempo_numero)
     return( I(-3) );           /* Numero do Arquivo nao encontrado.*/

 if (auxifil->tfilno < 0 )
     return(I(-2));

 return(auxifil->tfilno);
}

