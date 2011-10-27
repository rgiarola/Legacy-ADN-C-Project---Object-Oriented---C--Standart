#include <INCVIDEO.H>
#define MODULO_INCLUSAO
#include "adnmem.h"
#include "adnmem.c"

int pf_addr;

void main(void)
{
    unsigned int emm_handle,emm_handle2;
    char *pf_addr, *LocalPtr;
    int pages_needed, pages_free, ret, contador;

    MAP_MEMORY_LIST *MapMemory;

    int physical_page;
    int logical_page;
    int index;

    if (!ADNEmmInicializa())
       {
        printf ("\n EMM N„o Instalada ...");
        exit(1);
       }
     else
        printf ("\n EMM Instalada ...");

    pages_needed = 1;
    if (!ADNEmmPaginasLivres(pages_needed,&pages_free))
       {
        printf ("\n Nenhum Espa‡o Dispon¡vel ...");
        exit(1);
       }
     else
       {
        printf ("\n H  Espa‡o Dispon¡vel para %d P ginas...",pages_free);
       }

    if (!ADNEmmAlocaPaginas(pages_needed,&emm_handle))
       {
        printf ("\n Falha na Aloca‡„o ...");
        exit(1);
       }

    /*
    if (!ADNEmm200AlocaPaginas(pages_needed,&emm_handle))
       {
        printf ("\n Falha na Aloca‡„o ...");
        exit(1);
       }
     */

    if ((LocalPtr=ADNEmm200LockPaginas(emm_handle))==NULL)
       {
        printf ("\n Houve Erro 0x0c!!!");
       }
     else
       {
        printf ("\n Legal! Deu Certo!");
        printf ("\n Ponteiro Retornado %p",LocalPtr); getch();
       }

    if (!ADNEmmDesalocaPaginas(emm_handle))
       {
        printf ("\n Erro Liberado ...");
        exit(1);
       }
 printf ("\n Bye ...");
 ret=ADNEmmMapMemoriaTam();
 printf ("\n Tamanho da Estrutura %d",ret);
 if (ret>0)
    {
     if ((MapMemory = malloc (sizeof (MAP_MEMORY_LIST)*ret))==NULL)
        {
         printf ("Erro Aloca‡„o ...");
         exit (1);
        }
     printf ("\n Vai Chamar a Maledita ..."); getch();
     if ((ret = ADNEmmMapLeitura(MapMemory))<0)
        {
         printf ("\n Desculpe Mas Erro No Map Memory");
         exit (1);
        }

     printf ("\n Deu Certo?"); getch();
     printf ("\n Numero de Entradas %d",ret);
     printf ("\n\n Estrutura do Map de Mem¢ria ...");
     for (contador=0; contador < ret; contador++)
        {
         printf ("\n Segmento %x No. P ginas F¡sicas %u",
                 (MapMemory+contador)->physic_page_segment,
                 (MapMemory+contador)->physic_page_number ); getch();
        }
     printf ("\n");
    }


 exit (0);
}



