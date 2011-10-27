#include <INCVIDEO.H>

INT2 VIDEO_tipo_vetor(posini,posfim,refer,caracter,cor,vetor)
INT2 posini, posfim, refer;
BYTE         caracter,
             cor;
INT2          vetor;
{
 VD_VOID *buffer_loc;
 INT2     tam_buffer,
         col,
         lin;
 tam_buffer  =  posfim - posini + 1;
 if (VIDEO_ALLOC_MEM(buffer_loc,tam_buffer+1) == VD_NULO)
    {
#ifdef DATABASE_CTREE
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_VDVECTOR);
#endif
     return(FALSE);
    }

 VIDEO_setmem(buffer_loc,tam_buffer,caracter);
 *(PTR_CAST(BYTE,buffer_loc) + tam_buffer) = '\0';
 if (vetor&VIDEO_VET_V)
    {
     col = refer;
     lin = posini;
    }
   else
    {
     col = posini;
     lin = refer;
    }
  VIDEO_tprt(col,lin,buffer_loc,cor,vetor);
  VIDEO_FREE_ALLOC_MEM(buffer_loc);
 return(TRUE);
}

