#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

#include "adnmem.h"
#include "adnmem.c"

void main(void)
{
    unsigned int emm_handle,emm_handle2;
    char *pf_addr;
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
        printf ("\n EMM N„o Instalada ...");

    pages_needed = 500;
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

    physical_page = 0;
    logical_page  = 0;
    if (!ADNEmmMapPaginas(emm_handle, physical_page, logical_page))
       {
        printf ("\n Erro Map Mem¢ria");
        exit(1);
       }

    if (!ADNEmmGetFrameAdres(&pf_addr))
       {
        printf ("\n Erro Conseguindo Page Frame Adress");
        exit(1);
       }
    printf ("\n Endere‡o %x %p %p",pf_addr,pf_addr,pf_addr+1);

    /*--------------------------------------------------------*/
    /* Allocate expanded memory pages.                        */
    /*--------------------------------------------------------*/
    if (!ADNEmmAlocaPaginas(pages_needed,
                                         &emm_handle2))
       {
        printf ("\n Falha na Aloca‡„o ...");
        exit(1);
       }

    /*--------------------------------------------------------*/
    /* Map in the required pages.                             */
    /*--------------------------------------------------------*/
    if (!ADNEmmMapPaginas(emm_handle2, 0, 0))
       {
        printf ("\n Erro Map Mem¢ria");
        exit(1);
       }

    /*--------------------------------------------------------*/
    /* Get expanded memory page frame address.                */
    /*--------------------------------------------------------*/
    if (!ADNEmmGetFrameAdres(&pf_addr))
       {
        printf ("\n Erro Conseguindo Page Frame Adress");
        exit(1);
       }
    printf ("\n Endere‡o %x %p %p",pf_addr,pf_addr,pf_addr+1);

    /*--------------------------------------------------------*/
    /* Write to expanded memory.                              */
    /*--------------------------------------------------------*/
    printf ("\n Gravou na EMM");
    for (index = 0; index < 0x3fff; index++)
        pf_addr[index] = index;

    /*--------------------------------------------------------*/
    /* Return expanded memory pages before exiting.           */
    /*--------------------------------------------------------*/
    printf ("\n Liberou Geral ...");
    if (!ADNEmmDesalocaPaginas(emm_handle))
       {
        printf ("\n Erro Liberado ...");
        exit(1);
       }

    if (!ADNEmmDesalocaPaginas(emm_handle2))
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



