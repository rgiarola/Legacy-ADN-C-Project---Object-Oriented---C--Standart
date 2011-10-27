#define MODULO_INCLUSAO
#include <INCVIDEO.H>
#include "adnmem.c"
#include "adnpool.c"

void main(void)
{
    char far *pf_addr, *LocalPtr1, *LocalPtr2, *LocalPtr3, *LocalPtr4;
    int  ret;
    unsigned segmento, offset;
    unsigned long Teste, *Teste2;

 if ((ret=AdnMemPreparaPool(0x10000))!=FALSE)
    {
     printf("Prepara‡„o POOL [%d]\n",ret);
     exit(1);
    }
 delay (100);

 if (AdnMemAlocPool (0x9fff, &LocalPtr1))
    {
     AdnMemLiberaPool();
    }
 if (!ADNEmmGetFrameAdres(&pf_addr))
	{
	 return (ADNMEM_ERRO_PAGEFRAME);
	}
 printf ("\n Address Base(%p) Alocado(%p)",pf_addr, LocalPtr1);     getch();

 printf ("\n Ref.    Base(%p) Alocado(%p)",pf_addr+1, LocalPtr1+1); getch();
 printf ("\n Agora Vai Inicializar ..."); getch();
 VIDEO_setmem(LocalPtr1,0x9fff,65);
 printf ("\n Inicializou? ..."); getch();
 delay (10);

 printf ("\n Efetuando Varredura ..."); getch();
 for (Teste=0; Teste < (0x9fff); Teste++)
    {
     // printf ("%p",(LocalPtr1+Teste+4));
     if (*(LocalPtr1+Teste)!=65)
        {
         printf ("\n Integridade Falha em %ld...",Teste);
         break;
        }
    }
 printf ("\n Fim Varredura 1...");
 AdnMemLiberaPool ();

 printf ("\n Efetuando Varredura ..."); getch();
 for (Teste=0; Teste < (0x9fff); Teste++)
    {
     if (*(LocalPtr1+Teste)!=65)
        {
         printf ("\n Integridade Falha em %ld...",Teste);
         break;
        }
    }
 printf ("\n Fim Varredura 2...");
 printf ("\n FIM ...");

 exit (0);
}



