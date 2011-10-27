/* ============================================================================
   CTREE_keynm()  - Dado o nome do indice, esta funcao retorna o numero ctree
                    do indice.
   CTKEYNM()      - Nome abreviado.
   PARAMETRO:       Nome do indice.
   RETORNA:         O ctree numero do indice, em erro retorna um numero
                    negativo.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_keynm(nome_indice)
char *nome_indice;
{
 IDE_TABREFERDODA *elemento;
 static INT2       tabela[5] = {-1,-1,-1,-1,-1};
 INT2              cont,*tab;

 for (tab = tabela,cont = 0;cont < 5 && *tab > -1;cont++,tab++)
     if (!strcmp(nome_indice,
                (VIDEO_bufparamarq->bufdodas+*tab)->nome) &&
                (VIDEO_bufparamarq->bufdodas+*tab)->tipo == 2)
        return((VIDEO_bufparamarq->bufdodas+*tab)->numero);

 if (!nome_indice)
     return(I(-1));

 if ((elemento = VIDEO_elemento_tabrefer(nome_indice,2)) ==
      VD_NILL(IDE_TABREFERDODA))
     return(I(-2));    /* Nome do Indice nao encontrado.*/

 VIDEO_movbloco(&tabela[1],&tabela[0],sizeof(INT2)*4);
 tabela[0] = elemento->numero;

 return(elemento->numero);
}

/*
 register INT2   posicao_indice=0;
 IDE_ARQUIVOS **auxifil;
 IDE_INDEX     *work_indice;

 if( nome_indice == VD_NILL(char) )
   return( I(-1) );

 auxifil = ATIVO_IFIL;

 while( *auxifil )
   {
    work_indice = (*auxifil)->ix;

    posicao_indice = 0;
    while( posicao_indice < (*auxifil)->dnumidx )
      {
       if( !strcmp( work_indice->ridxnam, nome_indice) )
          return( (*auxifil)->dfilno+posicao_indice+1);
       ++posicao_indice;
       ++work_indice;
      }

    ++auxifil;

   }

 return( I(-2) );
*/

