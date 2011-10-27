#include <INCVIDEO.H>

INT2  VIDEO_movequadro(coli,colf,lini,linf,col,lin,flagsombra,atributo,
                      funcgettcl)
INT2  *coli, *colf,
     *lini, *linf,
     *col , *lin;
BYTE flagsombra,atributo;
INT2  (*funcgettcl)();
{
 VD_VOID *buffer;
 BYTE    ascii,
         scan;

 if (VIDEO_ALLOC_MEM(buffer,(*(colf)-*(coli)+1)*
                            (*(linf)-*(lini)+1)*2) == VD_NULO)
     return(FALSE);

 VD_lertela(*(coli),*(colf),*(lini),*(linf),buffer);
#ifdef VIDEO_UNIX
   VIDEO_UNIX_refresh_tela();
#endif
 do
  {
   (*funcgettcl)(&ascii,&scan);

   switch(scan)
    {
     case SOBE :if (*(lini) == 1)
                   continue;
                --*(lini),
                --*(linf);
                --*(lin);
                break;

#if defined(__VIDEO_DIM_TELA_CARGA_PARAMETROS)
     case DESCE :if ((*(linf)  + flagsombra) >=
                    VIDEO_dim_tela_parametros->VIDEO_maxlin)
                   continue;
#else
     case DESCE :if ((*(linf)  + flagsombra) >= VD_maxlin)
                   continue;
#endif
                ++*(lini),
                ++*(linf);
                ++*(lin);
                break;

     case ESQUERDA :if (*(coli) == 1)
                   continue;

                --*(coli),
                --*(colf);
                --*(col);
                break;

#if defined(__VIDEO_DIM_TELA_CARGA_PARAMETROS)
     case DIREITA :if ((*(colf) + flagsombra) >=
                      VIDEO_dim_tela_parametros->VIDEO_maxcol)
                   continue;
#else
     case DIREITA :if ((*(colf) + flagsombra) >= VD_maxcol)
                   continue;
#endif
                ++*(coli),
                ++*(colf);
                ++*(col);
                break;
  
     case ESCAPESCAN : VIDEO_FREE_ALLOC_MEM(buffer);
                       return(TRUE);

     default         : continue;
    }
   
   if (VD_POPWIN() < 0 ||
       VD_PUSHWIN(*(coli),*(colf)+flagsombra,*(lini),*(linf)+flagsombra) < 0)
      {
       VIDEO_FREE_ALLOC_MEM(buffer);
       return(TRUE);
      }

   if (flagsombra)
      {
       if (!VD_setatrib(*(colf)+1,*(colf)+1,*(lini)+1,*(linf)+1,atributo) ||
           !VD_setatrib(*(coli)+1,*(colf)+1,*(linf)+1,*(linf)+1,atributo))
          {
           VIDEO_FREE_ALLOC_MEM(buffer);
           return(TRUE);
          }
      }
   VD_grvtela(*(coli),*(colf),*(lini),*(linf),buffer);
#ifdef VIDEO_UNIX
   VIDEO_UNIX_refresh_tela();
#endif
  }while(TRUE);
}
