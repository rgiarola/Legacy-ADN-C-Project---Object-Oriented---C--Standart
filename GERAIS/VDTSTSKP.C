#include <INCVIDEO.H>

INT2 VIDEO_testa_tabskip(ascii,scan,tabskip)
BYTE           ascii,
               scan;
register WORD  *tabskip;
{
 WORD teste,
      cont = 0;

 teste = W(W(ascii)|W(W(scan)<<8));
 while(*(tabskip))
  {
   if (*(tabskip++) == teste)
       return(++cont);
   ++cont;
  }
 return(FALSE);
} 

