#include <INCVIDEO.H>

long double VIDEO_atold_t(buffer,tamanho)
char *buffer;
INT2  tamanho;
{
 char buffer_loc[50],
      *erro;
 long double num;

 VIDEO_movbloco(buffer_loc,buffer,tamanho);
 buffer_loc[tamanho] = '\0';
 num = _strtold(buffer_loc,&erro);
 if (*erro)
    {
     sprintf(buffer_loc,VIDEO_GERAIS_conv_double,buffer,erro);
     VIDEO_mostra_mens_erro(buffer_loc,TRUE);
     return(LD(-1.0));
    }
 return(num);
}

