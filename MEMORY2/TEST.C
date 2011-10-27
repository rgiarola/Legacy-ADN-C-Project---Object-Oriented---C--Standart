#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <alloc.h>
#include <dos.h>
#include <conio.h>

#include "memory.h"

#define TAMANHO_ALLOC 32000
int main ()
{
 int   Alocadores[500];
 int   pos;
 long  Memoria=0L;
 char  *Ptr=NULL;

 memset (Alocadores,0,500); // Zerando

 clrscr();
 printf ("Inciando Aloca‡„o ...");
 for (pos=0;pos<500;pos++)
    {
     gotoxy (1,2);
     Alocadores[pos] = xalloc (TAMANHO_ALLOC, 1);    // Tamanho X 1Linha
     if (Alocadores[pos])
        {
         Memoria += TAMANHO_ALLOC;
         printf ("%06ld Bytes Alocados (Pos %d) (Allocador %d)",Memoria,pos,
                 Alocadores);
        }
      else
        {
         printf ("\n Erro Alocacao %d",pos); getch();
         break;
        }
     delay (50);
    }

 Ptr = xget (0,Alocadores[0]);
 if (Ptr)
    {
     printf ("\n Manipulando MEM");
     memset (Ptr,'0',TAMANHO_ALLOC); // Zerando
     * (Ptr+30)=0;
     printf ("\nResultado ... %s",Ptr);
    }
 else
    {
     printf ("\n Erro de Leitura ...");
    }


 /*
 gotoxy (4,1);
 printf ("Desalocando ...");
 --pos;
 while (pos>0)
    {
     xfree (Allocadores[pos]);

     Memoria -= TAMANHO_ALLOC;
     gotoxy (5,1);
     printf ("%06ld Bytes a Desalocar ainda (Pos %d)",Memoria,pos);

     pos --;
     delay (50);
    }
  */
}

