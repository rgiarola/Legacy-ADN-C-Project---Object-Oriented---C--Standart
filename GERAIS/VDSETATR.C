#include <INCVIDEO.H>

INT2 VIDEO_setatrib(coli,colf,lini,linf,cor)
register INT2  coli ,colf,
              lini ,linf;
register BYTE cor;
{
   if (VIDEO_teste_4(coli,colf,lini,linf))
      {
       VD_VOID *buffer;
       register INT2  tam;

       tam = (colf-coli+1)*(linf-lini+1);
       if (VIDEO_ALLOC_MEM(buffer,tam) == VD_NULO)
          {
           VIDEO_mostra_mens_erro_alloc(ALOCACAO_SETATRIB);
           return(FALSE);
          }
       cor = VIDEO_monta_cor(cor);
       VIDEO_setmem(buffer,tam,cor);
       VIDEO_grvatrib(coli,colf,lini,linf,buffer);
       VIDEO_FREE_ALLOC_MEM(buffer);
       return(TRUE);
      }
 return(FALSE);
}
