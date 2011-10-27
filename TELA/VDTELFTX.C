#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_faixa_texto(inicio,fim,elemento)
char *inicio,
     *fim,
     *elemento;
{
 return(!((strcmp(elemento,inicio) >= 0) &&
     (strcmp(elemento,fim) <= 0)));
}




