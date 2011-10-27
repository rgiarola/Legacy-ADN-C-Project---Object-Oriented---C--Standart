#include <INCVIDEO.H>

VIDEO_EDITA_testa_sinalponto(buffer,autos,tamanho,decimais)
char  *buffer;
WORD  autos;
INT2   tamanho,
      decimais;
{
 INT2  dec = 0,
      tamaux,
      sinal,
      flagcont = FALSE;

 sinal = (((autos&(VIDEO_EDITA_SINALMENOS|VIDEO_EDITA_SINALMAIS))>0) &&
           !(*buffer == '-' || *buffer == '+'));

 tamaux = strlen(buffer) + (((autos&(VIDEO_EDITA_SINALMENOS|
          VIDEO_EDITA_SINALMAIS))>0) && !(*buffer == '-' || *buffer == '+'));

 while(*buffer)
  {
   if (flagcont)
      ++dec;
   if (*buffer == '.')
       flagcont = TRUE;
   ++buffer;
  }

 tamaux += ((!flagcont && (autos&VIDEO_EDITA_EDPONTO))+ decimais - dec);
 return(tamanho>=tamaux && dec <= decimais);
}
