#include <INCVIDEO.H>

int VIDEO_opertela(coli,colf,lini,linf,buffer,opcao)
int  coli, colf, lini, linf;
char *buffer;
int  opcao;
{
 register int numlins,cont_lin,cont_pos,
              tamanho;
 char far     *pointeraux;

 if (!VIDEO_teste_4(coli,colf,lini,linf))
    return(VIDEO_ERRO_OPERTE_param_invalido);

 numlins  = linf - lini + 1;
 tamanho  = (colf - coli + 1) * 2;
 pointeraux = VIDEO_FISICO(lini,coli);

 switch(opcao)
  {
   case VIDEO_GRAVACAO:
                       do
                        {
#ifdef VIDEO_UNIX
                         VIDEO_movbloco(pointeraux,buffer,tamanho);
#endif
#ifdef VIDEO_DOS
                         movedata(VIDEO_FP_SEG(buffer),VIDEO_FP_OFF(buffer),
                             FP_SEG(pointeraux),FP_OFF(pointeraux),tamanho);
#endif
                         buffer += tamanho;
                         pointeraux += 160;
                        }while(--numlins);

#ifdef VIDEO_UNIX
                       if (VIDEO_UNIX_flag_video&VIDEO_UNIX_AUTOREFRESH)
                           VIDEO_unix_refresh();
#endif
                       break;

   case VIDEO_LEITURA:do
                       {
#ifdef VIDEO_UNIX
                         VIDEO_movbloco(buffer,pointeraux,tamanho);
#endif
#ifdef VIDEO_DOS
                        movedata(FP_SEG(pointeraux),FP_OFF(pointeraux),
                        VIDEO_FP_SEG(buffer),VIDEO_FP_OFF(buffer),tamanho);
#endif
                        buffer += tamanho;
                        pointeraux += 160;
                       }while(--numlins);
                       return(TRUE);

   case VIDEO_LERATRIB:do
                        {
                         char far *ptrfim, far *ptraux;
                         ptraux = pointeraux;
                         ptrfim = pointeraux + tamanho;
                         ++pointeraux;
                         do
                          {
                           *buffer = *pointeraux;
                           pointeraux += 2;
                          }while (pointeraux < ptrfim);
                         pointeraux = ptraux + 160;
                        }while(--numlins);
                       return(TRUE);

   case VIDEO_GRVATRIB:
                       do
                        {
                         char far *ptrfim, far *ptraux;
                         ptraux = pointeraux;
                         ptrfim = pointeraux + tamanho;
                         ++pointeraux;
                         do
                          {
                           *pointeraux = *buffer;
                           pointeraux += 2;
                          }while (pointeraux < ptrfim);
                         pointeraux = ptraux + 160;
                        }while(--numlins);
#ifdef VIDEO_UNIX
                       if (VIDEO_UNIX_flag_video&VIDEO_UNIX_AUTOREFRESH)
                           VIDEO_unix_refresh();
#endif
                       break;

   default:return(VIDEO_ERRO_OPERTE_servico_invalido);
  }	

#ifdef VIDEO_UNIX
 if (lini < VIDEO_unix_minlin)                                 
    VIDEO_unix_minlin = lini;                                  
                                                               
 if (linf > VIDEO_unix_maxlin)                                 
     VIDEO_unix_maxlin = linf;                                 
                                                               
 if (coli < VIDEO_unix_mincol)                                 
    VIDEO_unix_mincol = coli;                                  
                                                               
 if (colf > VIDEO_unix_maxcol)                                 
     VIDEO_unix_maxcol = colf;                                 
#endif

 return(TRUE);
}

