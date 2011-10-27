#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_consiste_faixa(elemento,faixa,functesta)
char             *elemento;
char             *faixa;
INT2  (*functesta)(char *inicio,char *fim,char *elemento);
{
 char   *inicio,
        *fim,
        *aux1,
        *aux2,
        *aux3;
 INT2    flagdec,
        tamanho;

 aux1 = aux2 = faixa;
 while(*aux1 != ',' && *aux1)
      ++aux1;
 aux3 = aux1 + 1;
 if (!*aux1)
    {
     char buffer[200];
     sprintf(buffer,VIDEO_erro_montagem_faixa,faixa);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_montagem_faixa);
     return(FALSE);
    }

 if (aux1 != faixa)
    {
     --aux1;
     while(*aux1 == ' ' && aux1 != faixa)
           --aux1;
     if (aux1 != faixa)
         while(*aux2 == ' ')
               ++aux2;
    }
 ++aux1;
 tamanho = W(aux1) - W(aux2);
 if (VIDEO_ALLOC_MEM(inicio,tamanho + 1) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONS_FAIXA_1);
     return(FALSE);
    }
 VIDEO_movbloco(inicio,aux2,tamanho);
 *(inicio + tamanho) = '\0';
 aux1 = aux3;
 aux2 = aux1 + strlen(aux3);
 if (*aux1)
    {
     while(*aux1 == ' ' && *aux1)
           ++aux1;
     if (*aux1)
        {
         --aux2;
         while(*aux2 == ' ')
           --aux2;
         ++aux2;
        }
    }
 tamanho = W(aux2) - W(aux1);
 if (VIDEO_ALLOC_MEM(fim,tamanho + 1) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONS_FAIXA_2);
     VIDEO_FREE_ALLOC_MEM(inicio);
     return(FALSE);
    }

 VIDEO_movbloco(fim,aux1,tamanho);
 *(fim + tamanho) = '\0';
 tamanho = (*functesta)(inicio,fim,elemento);
 VIDEO_FREE_ALLOC_MEM(inicio);
 VIDEO_FREE_ALLOC_MEM(fim);
 return(tamanho);
}

