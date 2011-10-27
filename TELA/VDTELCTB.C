#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_consiste_tabela(elemento,tabela,functesta,tamanho)
char *elemento,
     **tabela;
INT2  (*functesta)(),
     tamanho;
{
 INT2  cont, tamaux, tamelem;
 char *pointer;

 cont = 0;
 tamelem = strlen(elemento);
 do
  {
   if (!tabela[cont])
      return(TRUE);

   if (tamanho > 0)
      {
       if (!(*functesta)(elemento,tabela[cont],tamanho))
          return(FALSE);
      }
    else
     if (tamanho < 0)
        {
         if ((tamaux = strlen(tabela[cont])) < tamelem)
            {
             if (VIDEO_ALLOC_MEM(pointer,tamelem+1) == VD_NULO)
                {
                 VIDEO_mostra_mens_erro_alloc(ALOCACAO_CONS_TABELA);
                 return(TRUE);
                }
             VIDEO_setmem(pointer,tamelem,' ');
             VIDEO_movbloco(pointer,tabela[cont],tamaux);
             *(pointer+tamelem) = '\0';
            }
          else
            pointer = tabela[cont];

         tamaux = (*functesta)(elemento,pointer,tamelem);

         if (pointer != tabela[cont])
             VIDEO_FREE_ALLOC_MEM(pointer);

         if (!tamaux)
            return(FALSE);
        }
      else
       if (!(*functesta)(elemento,tabela[cont]))
          return(FALSE);
   ++cont;
  }while(TRUE);
}

