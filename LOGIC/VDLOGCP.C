#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

int VIDEO_LOGIC_analise(linha,retorno)
char               *linha;
VIDEO_LOGIC_OBJETO *retorno;
{
 char *expresao;
 VIDEO_LOGIC_OBJETO *elemento;
 int                ret;
 char               *expcomp;

 if (VIDEO_ALLOC_MEM(expcomp,(strlen(linha)+2)) == VD_NULO)
     return(VIDEO_LOGIC_ALLOCMEM);

 if (VIDEO_ALLOC_MEM(VIDEO_LOGIC_objetos,sizeof(VIDEO_LOGIC_OBJETO)*51) == VD_NULO)
    {
     VIDEO_FREE_ALLOC_MEM(expcomp);
     return(VIDEO_LOGIC_ALLOCMEM);
    }

 sprintf(expcomp,"@(%s)",linha);

 if ((expresao = strchr(expcomp,'@')) == VD_NULO)
    {
     VIDEO_FREE_ALLOC_MEM(expcomp);
     VIDEO_FREE_ALLOC_MEM(VIDEO_LOGIC_objetos);
	 return(VIDEO_LOGIC_LINHA_NULA);
    }

 VIDEO_setmem(VIDEO_LOGIC_objetos,51*sizeof(VIDEO_LOGIC_OBJETO),0);

 elemento = VIDEO_LOGIC_objetos;
               
 ret = VIDEO_LOGIC_analise_expresao(expresao+1,retorno,&elemento,0);

 VIDEO_FREE_ALLOC_MEM(expcomp);

 VIDEO_FREE_ALLOC_MEM(VIDEO_LOGIC_objetos);

 return(ret);
}




