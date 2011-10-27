#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_faixa_numero(inicio,fim,elemento)
char *inicio,
     *fim,
     *elemento;
{
 INT2 tam1,tam2,tam3;

 tam3 = strlen(elemento);
 tam1 = strlen(inicio);
 tam2 = strlen(fim);

 if (tam3 > tam1)
    tam1 = tam3;
 if (tam3 > tam2)
    tam2 = tam3;

 if ((VIDEO_TELA_compara_numero(elemento,inicio,tam1) >= 0) &&
     (VIDEO_TELA_compara_numero(elemento,fim,tam2)    <= 0))
     return(FALSE);
 return(TRUE);
}

