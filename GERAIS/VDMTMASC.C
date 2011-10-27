#include <INCVIDEO.H>

INT2 VIDEO_monta_mascara(entrada,mascara,saida,flaglimpa,flagmostra)
char *entrada,
     *mascara,
     *saida;
char flaglimpa;
WORD flagmostra;
{
 char buffer[200],
      work[20];
 char *workmasc,
      *workbuf,
      *workarea,
      *workbuffer,
      sinal;
 INT2  tammascara,
      tambuffer;

 workmasc = mascara  + ((tammascara = strlen(mascara)) - (tammascara > 0));
 workbuf  = entrada  + ((tambuffer = strlen(entrada))  - (tambuffer  > 0));
 workarea = &work[19];
 *workarea = '\0';
 workbuffer = VD_NULO;

 sinal = VD_NULO;
 do
  {
   --workarea;
   switch(*workmasc)
    {
      case 'Z' :
      case 'z' :
      case 'B' :
      case 'b' :if (workbuf >= entrada)
                   {
                    if (*workbuf != '-')
                       *workarea = flagmostra ? '*' : *workbuf;
                     else
                       {
                        ++workarea;
                        ++workmasc;
                        sinal = '-';
					   }
                    --workbuf;
                   }
                 else
                   {
                    if (!workbuffer)
                        workbuffer = workarea+1;
                    *workarea = flagmostra ? '*' : ' ';
                   }
                break;

      case '9' :if (workbuf >= entrada)
                   {
                    if (*workbuf != '-')
                       *workarea = flagmostra ? '*' : *workbuf;
                     else
                       {
                        ++workarea;
                        ++workmasc;
                        sinal = '-';
					   }
                    --workbuf;
                   }
                 else
                   {
                    workbuffer = workarea;
                    *workarea  = flagmostra ? '*' : '0';
                   }
                break;

      case 'S' :
      case 's' :if (workbuf >= entrada)
                   {
                    if (*workbuf != '-')
                       *workarea = flagmostra ? '*' : *workbuf;
                     else
                       {
                        ++workarea;
                        ++workmasc;
                        sinal = '-';
					   }
                    --workbuf;
                   }
                 else
                   {
                    if (!workbuffer)
                        workbuffer = workarea+1;
                    *workarea = flagmostra ? '*' : ' ';
                   }
                break;

      default :*workarea = flagmostra ? '*' : *workmasc;
    };
  }while(workmasc-- != mascara);

 if (!workbuffer)
     workbuffer = workarea;

 workbuf = &work[19];
/*
 VD_gtxy(1,1);
 printf("1[%s][%s][%s]            ",workbuffer,entrada,mascara);
 getch();
*/
 if (flaglimpa && !flagmostra)
    {
     while(!(((*workbuffer >= '0') && (*workbuffer <= '9'))))
       ++workbuffer;

     VIDEO_setmem(workarea,tammascara-strlen(workbuffer),flaglimpa);
    }

 if (sinal)
    {
     if (workbuffer > workarea)
         --workbuffer;
       *workbuffer = flagmostra ? '*' : '-';
    }

/*
 VD_gtxy(1,1);
 printf("2[%s][%s][%s]            ",workbuffer,entrada,mascara);
 getch();
*/
 strcpy(saida,workarea);
 return(TRUE);
}
