#include <INCVIDEO.H>

unsigned long int VIDEO_atoul_t(buffer,tamanho)
char *buffer;
INT2  tamanho;
{
 char     buffer_loc[50],
          *erro;
 unsigned long int num;

 VIDEO_movbloco(buffer_loc,buffer,tamanho);
 buffer_loc[tamanho] = '\0';
 return(strtoul(buffer_loc,&erro,10));
}

