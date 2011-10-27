#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_coloca_ponto(buffer,decimais)
char  *buffer;
INT2   decimais;
{
 INT2     tam;
 char    bufferaux[30];
 BOOLEAN sinal;

 if (*buffer == '-')
    {
     sinal = TRUE;
     VIDEO_copbloco(buffer,buffer+1,strlen(buffer));
    }
  else
   sinal = FALSE;

 if ((tam = strlen(buffer)) <= decimais)
	{
     VIDEO_setmem(bufferaux,decimais+2,'0');
	 strcpy(&bufferaux[decimais+2-tam],buffer);
	 strcpy(buffer,bufferaux);
	}
  else
    VIDEO_copbloco(buffer+(tam-decimais+1),buffer+(tam-decimais),decimais + 1);

 tam = strlen(buffer);
 *(buffer+(tam-decimais-1)) = '.';

 if (sinal)
    {
     VIDEO_copbloco(buffer+1,buffer,strlen(buffer));
     *buffer = '-';
    }

  return(TRUE);
}
