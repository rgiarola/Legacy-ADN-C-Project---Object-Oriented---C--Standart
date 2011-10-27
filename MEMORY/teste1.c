#include "adnmem.c"

// int pf_addr;

void main(void)
{
    unsigned int emm_handle,emm_handle2;
    char *pf_addr;
    int pages_needed, pages_free, ret, contador, segmento,offset;

    MAP_MEMORY_LIST *MapMemory;

    int physical_page;
    int logical_page;
    long index;

    if (!ADNEmmInicializa())
       {
        printf ("\n EMM N„o Instalada ...");
        exit(1);
       }
     else
        printf ("\n EMM Instalada ...");

    pages_needed = 20;
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

    for (ret=0;ret<20;ret++)
        {
         if (!ADNEmmMapPaginas(emm_handle, physical_page, ret))
            {
             printf ("\n Erro Map Mem¢ria: P gina L¢gica %d",ret);
             ADNEmmDesalocaPaginas(emm_handle);
             exit(1);
            }
        }

    if (!ADNEmmMapPaginas(emm_handle, physical_page, 0xffff))
       {
        printf ("\n Erro Map Mem¢ria: P gina L¢gica %d",ret);
        ADNEmmDesalocaPaginas(emm_handle);
        exit(1);
       }

    printf ("\n P ginas F¡sica 1 em Lock"); getch();

    if (!ADNEmmGetFrameAdres(&pf_addr))
       {
        printf ("\n Erro Conseguindo Page Frame Adress");
        exit(1);
       }
    printf ("\n Endere‡o %p",pf_addr);

    segmento  = FP_SEG(pf_addr); // +0x400;
    offset    = FP_OFF(pf_addr);
    printf ("\n Endere‡o Segmento %x Off %x",segmento,offset);
    pf_addr   = MK_FP (segmento,offset);
    printf ("\n Endere‡o %x %p",pf_addr,pf_addr); getch();


    /*--------------------------------------------------------*/
    /* Write to expanded memory.                              */
    /*--------------------------------------------------------*/

    printf ("\n Gravou na EMM");
    for (index = 0; index < ((0x4000*20)-1); index++)
        pf_addr[index] = index;
    printf ("\n Deu Certo?"); getch();

    /*--------------------------------------------------------*/
    /* Return expanded memory pages before exiting.           */
    /*--------------------------------------------------------*/
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

 printf ("\n Liberou Geral ...");
 if (!ADNEmmDesalocaPaginas(emm_handle))
    {
     printf ("\n Erro Liberado ...");
     exit(1);
    }



 exit (0);
}



