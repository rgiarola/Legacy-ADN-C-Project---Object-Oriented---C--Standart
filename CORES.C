#include <INCVIDEO.H>

main()
{
 register int lin, col;
          int coluna,
              cor=0;

 VD_CLS;
 for ( lin=0; lin<16; lin++)
  {
   coluna = 1;
   for ( col=0; col<16; col++)
    {
     char buffer[15];
     sprintf(buffer,"%3d",cor++);
     VD_tprt_l( col+coluna, lin+1, buffer, ((lin)|(col*16)) );
     coluna += 2;
    }
  }

 getch();
 return(0);

}

