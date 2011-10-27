#include<INCVIDEO.H>
#include "VDLINALF.H"

/*===========================================================================
                               FILTRA LINHA
===========================================================================*/
char *VIDEO_MCLIN_filtra_linha(expande)
VIDEO_MCLIN_STR_EXPAND *expande;
{
 int  tamanho;
 char *linha,*auxlinha;

 do
  {
   if ((linha = VIDEO_MCLIN_pega_linha(expande)) == VD_NULO)
      return(VD_NULO);

   while(*linha == ' ' || *linha == VD_TAB)
     ++linha;

   if ((tamanho = strlen(linha)) == 0)
       continue;

   auxlinha = linha + tamanho -1;

   while((linha != auxlinha) && (*auxlinha == ' ' || *auxlinha == VD_TAB))
     *auxlinha-- = 0;

   break;
  }while(TRUE);

 return(linha);
}

