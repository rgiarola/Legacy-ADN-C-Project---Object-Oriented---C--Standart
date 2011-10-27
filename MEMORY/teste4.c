#define MODULO_INCLUSAO
#include "adnmem.c"
#include "adnpool.c"

void main(void)
{
    char far *pf_addr, *LocalPtr1, *LocalPtr2, *LocalPtr3, *LocalPtr4;
    int  ret;
    unsigned segmento, offset;
    unsigned long Teste, *Teste2;
/*
 if ((ret=AdnMemPreparaPool(65536L))!=FALSE)
    {
     printf("Prepara‡„o POOL [%d]\n",ret);
     exit(1);
    }
  */

 Teste = 2;
 printf ("\n Teste1 %ld Teste2 %ld Teste3 %ld Teste4 %ld",
 Teste << 1, Teste << 2, Teste << 3, Teste << 4);getch();

 segmento = 16;
 offset   =  1;
 Teste2 = MK_FP (segmento,offset);
 printf ("\n %p %ld %x",Teste, Teste, Teste); getch();

 if (!ADNEmmInicializa())
    {
     printf ("\n EMM N„o Instalada ...");
     exit(1);
    }
  else
     printf ("\n EMM Instalada ...");


 if (!ADNEmmGetFrameAdres(&pf_addr))
	{
	 return (ADNMEM_ERRO_PAGEFRAME);
	}
 printf ("\n Address %x %p",pf_addr, pf_addr); getch();
 printf ("\n Address %p %x",pf_addr,pf_addr); getch();
 segmento = FP_SEG(pf_addr);
 offset   = FP_OFF(pf_addr);
 printf ("\n Segmento %x OffSet %x",segmento,offset); getch();
 LocalPtr1 = ADNBuildPtr (segmento, offset);
 LocalPtr2 = MK_FP       (segmento, offset);

 printf ("\n%p %p",LocalPtr1+1,LocalPtr2); getch();
 LocalPtr3 = malloc (10);
 LocalPtr4 = malloc (10);
 printf ("\n%p %p",LocalPtr3+1,LocalPtr4); getch();

 printf ("\n %x:%x %x:%x",FP_SEG (LocalPtr1),FP_OFF(LocalPtr1),
                          FP_SEG (LocalPtr2),FP_OFF(LocalPtr2)); getch();
 printf ("\n %x:%x %x:%x",FP_SEG (LocalPtr3),FP_OFF(LocalPtr3),
                          FP_SEG (LocalPtr4),FP_OFF(LocalPtr4)); getch();



 free (LocalPtr3);
 free (LocalPtr4);

 // AdnMemLiberaPool ();

 exit (0);
}



