#include <INCVIDEO.H>

long int VIDEO_atol_t(buffer,tamanho)
char *buffer;
INT2  tamanho;
{
 char     buffer_loc[50],
		  *erro;
 long int num;

 VIDEO_movbloco(buffer_loc,buffer,tamanho);
 buffer_loc[tamanho] = '\0';
 num = strtol(buffer_loc,&erro,10);
 if (*erro)
    {
     sprintf(buffer_loc,VIDEO_GERAIS_conv_long,buffer,erro);
     VIDEO_mostra_mens_erro(buffer_loc,TRUE);
     return(-1L);
    }
 return(num);
}


