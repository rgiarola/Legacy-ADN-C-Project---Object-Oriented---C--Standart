#include<INCVIDEO.H>

VD_VOID VIDEO_EDITA_mascara_posiciona(mascara,bflocal,coli,col,pos)
char *mascara,
     *bflocal;
INT2  coli,
     *col,
     pos;
{
 INT2 tam;

 *col = coli;

 if (((tam = strlen(bflocal)) == 0 && pos != 0) || (pos > tam) || !mascara ||
      !strlen(mascara))
    return;
 do
  {
   switch(*mascara++)
    {
     case 'Z' :
     case 'z' :
     case '9' :
     case 'B' :
     case 'b' :
     case 'U' :
     case 'u' :
     case 'L' :
     case 'E' :
     case 'e' :
     case 'l' :
     case 'C' :
     case 'c' :
     case 'O' :
     case 'F' :
     case 'f' :
     case 'H' :
     case 'X' :
     case 'x' :
     case 'Q' :
     case 'T' :
     case 't' :
     case 'q' :
     case 'D' :
     case 'M' :
     case 'A' :
     case 'h' :
     case 'm' :
     case 's' :
     case 'G' :if (!pos)
                   return;
               --pos;
    }
   ++*col;
  }while(TRUE);
}

