/* ============================================================================ 
   CTREE_tmpkey() - Dado o temporario numero ctree do indice, consegue o numero
                    o numero principal do indice.
   CTFILKEY()     - Nome abreviado.
   PARAMETRO:       Temporario Numero Ctree do Indice.
   RETORNA:         O numero ctree do indice, em erro retorna um numero
                    negativo.
   ============================================================================ */
#include <INCVIDEO.H>

INT2  CTREE_tmpkey( tempo_indice )
INT2  tempo_indice;
{
 INT2          tempo_arquivo,
              real_arquivo,
              real_indice;
 IDE_ARQUIVOS **auxifil;

 if(tempo_indice<=0)
   return(I(-1));

 if( (tempo_arquivo=CTREE_keyfil(tempo_indice ))<0 )
   return(I(-2));

 if( (real_arquivo =CTREE_tmpfil(tempo_arquivo))<0 )
   return(I(-3));

 return( real_arquivo + (tempo_indice - tempo_arquivo) );

}

