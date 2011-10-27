#include<INCVIDEO.H>

char *VIDEO_EDITA_expande_mascara(mascara)
char *mascara;
{
 char *destino,
      *ret;

 if (!mascara)
    return(VIDEO_NILL(char));

 if ((ret = destino = VIDEO_alloc_parametros(128)) == VIDEO_NULO)
	{
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_EXP_MASCARA);
     return(VIDEO_NILL(char));
	}

 while(*mascara)
  {
   if (*mascara == '@')
      {
       char buffer[12],
            *aux;
       INT2  tam;
       ++mascara;
       aux = buffer;
       while((*mascara >= '0') && (*mascara <= '9'))
            *aux++ = *mascara++;
       *aux = '\0';
       if ((tam = atoi(buffer)) == 0)
          {
           VIDEO_free_alloc_parametros(destino);
           return(VIDEO_NILL(char));
          }
       VIDEO_setmem(destino,tam,*mascara);
       destino += tam;
      }
    else
      *destino++ = *mascara;
   ++mascara;
  }
 *destino = '\0';
 return(ret);
}

