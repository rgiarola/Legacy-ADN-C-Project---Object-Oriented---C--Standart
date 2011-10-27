#include <INCVIDEO.H>

INT2 VIDEO_EDITA_campo_testaponto(buffer,decimais)
char  *buffer;
INT2   decimais;
{
 BOOLEAN flagcont = FALSE;

 while(*buffer)
  {
   if (flagcont)
      --decimais;
   if (*buffer == '.')
      flagcont = TRUE;
   ++buffer;
  }
 return(decimais >= 0);
}
