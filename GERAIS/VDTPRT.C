#include <INCVIDEO.H>

BYTE VIDEO_flag_display = FALSE;

int VIDEO_tprt(col,lin,buffer,cor,vetor)
int  col,
     lin;
char *buffer;
BYTE cor;
int  vetor;
{
 char far *pointeraux;
 int      aux;

#ifdef VIDEO_UNIX
  int tamanho;
#endif

 if (!VIDEO_teste_2(col,lin))
    return(-1);

 if (vetor)
    {
     if ((lin-1+strlen(buffer)) > VIDEO_MAXLIN)
        return(-2);
    }
  else
    if (((lin-1)*(col-1)+strlen(buffer)) >= (VIDEO_MAXCOL*VIDEO_MAXLIN))
        return(-3);

 pointeraux = VIDEO_FISICO(lin,col);

 cor = VIDEO_monta_cor(cor);

#ifdef VIDEO_UNIX
 if ((tamanho = (strlen(buffer)-1)) <= 0)
    tamanho = 0;
#endif

 while(*buffer)
  {
   *pointeraux   = *buffer;
   ++pointeraux;
   if (cor)
       *pointeraux = cor;

   ++buffer;
   if (vetor)
      pointeraux += 159;
    else
      ++pointeraux;
  }

#ifdef VIDEO_UNIX

 if (lin < VIDEO_unix_minlin)
    VIDEO_unix_minlin = lin;

 if (lin > VIDEO_unix_maxlin)
     VIDEO_unix_maxlin = lin; 

 if (col < VIDEO_unix_mincol)
    VIDEO_unix_mincol = col;
 
 if (!vetor)
    {
     if ((col+tamanho) > VIDEO_unix_maxcol)                 
         VIDEO_unix_maxcol = col+tamanho;                   
    } 
  else
    if (col > VIDEO_unix_maxcol)
        VIDEO_unix_maxcol = col;

 if (VIDEO_UNIX_flag_video&VIDEO_UNIX_AUTOREFRESH)
    VIDEO_unix_refresh();

#endif   

 return(TRUE);
}


