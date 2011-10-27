/* ============================================================================ 
   CTREE_keyfil() - Dado o ctree numero do indice, consegue o numero do arquivo.
   CTFILKEY()     - Nome abreviado.
   PARAMETRO:       Ctree Numero do Indice.
   RETORNA:         O ctree numero do arquivo, em erro retorna um numero
                    negativo.
   ============================================================================ */
#include <INCVIDEO.H>

INT2  CTREE_keyfil( numero_indice )
INT2  numero_indice;
{
 IDE_TABREFERDODA *elemento;

 if (numero_indice < 1)
     return( I(-1) );

 if (numero_indice >= (VIDEO_bufparamarq->numarq+
                       VIDEO_bufparamarq->numind))
     return( I(-1) );    /* Numero do Arquivo nao encontrado.*/

 elemento = VIDEO_bufparamarq->bufdodas + numero_indice;

 if (elemento->numero != numero_indice)
     return( I(-1) );    /* Numero do Arquivo nao encontrado.*/

 do
  {
   if (elemento->tipo == 1)
       return(elemento->numero);
  }while((elemento--)->numero);

 return( I(-2) );    /* Numero do Arquivo nao encontrado.*/
}

