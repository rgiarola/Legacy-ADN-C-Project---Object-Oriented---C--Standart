#include<INCVIDEO.H>

INT2 VIDEO_EDITA_mascara_coldir(mascara,posmasc,col,posbuffer,fim)
char *mascara;
INT2  *posmasc,
     *col,
     *posbuffer,
     fim;
{
 mascara += *posmasc;
 do
  {
   if (*posbuffer >= fim || !*mascara)
      return(FALSE);
   ++*posmasc;
   ++*col;
   ++mascara;
   switch(*mascara)
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
     case 'G' :++*posbuffer;
               return(TRUE);
    }
  }while(TRUE);
}

