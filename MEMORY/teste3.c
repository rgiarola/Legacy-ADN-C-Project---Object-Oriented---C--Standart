#include "adnmem.c"

int pf_addr;

void main(void)
{
	unsigned int emm_handle,emm_handle2;
	char *pf_addr, *LocalPtr;
    int pages_needed, pages_free, ret, contador;
    char mensagem[] = "ISTO ê UMA MENSAGEM PARA VOC“S",
         retorno[100];

	MAP_MEMORY_LIST *MapMemory;

	int physical_page;
	int logical_page;
	long index;

	if (!ADNEmmInicializa())
	   {
		printf ("\n EMM NÑo Instalada ...");
		exit(1);
	   }
	 else
		printf ("\n EMM Instalada ...");

    pages_needed = 256;
	if (!ADNEmmPaginasLivres(pages_needed,&pages_free))
	   {
		printf ("\n Nenhum Espaáo Dispon°vel ...");
		exit(1);
	   }
	 else
	   {
		printf ("\n H† Espaáo Dispon°vel para %d P†ginas...",pages_free);
	   }

	if (!ADNEmmAlocaPaginas(pages_needed,&emm_handle))
	   {
		printf ("\n Falha na AlocaáÑo ...");
		exit(1);
	   }

	physical_page = 0;
	logical_page  = 0;
	// Isto Define Onde as P†ginas EstarÑo ...
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
	printf ("\n Endereáo %x %p %p",pf_addr,pf_addr,pf_addr+1);

	// No M°nimo Suspeito
	for (index = 0; index < ((0xffff*(pages_needed/4))-1); index++)
		pf_addr[index] = index;

    memcpy (pf_addr,mensagem,strlen(mensagem));
    memcpy (retorno, pf_addr, strlen(mensagem));
    printf ("\n Resultado: %s",retorno); getch();


	if (!ADNEmmDesalocaPaginas(emm_handle))
	   {
		printf ("\n Erro Liberado ...");
		exit(1);
	   }
 printf ("\n Bye ...");


 exit (0);
}



