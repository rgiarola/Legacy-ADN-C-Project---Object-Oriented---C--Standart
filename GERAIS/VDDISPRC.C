#include <INCVIDEO.H>

int VIDEO_cont_proc_tela(VD_VOID)
{
 static cont = 0;
 char   carac[] = {'|','/','-','\\'};
 VIDEO_plotcarac(VIDEO_mensagem_default.col,
                 VIDEO_mensagem_default.lin,carac[cont],0);
 cont = ++cont == 4 ? 0 : cont;

 return(FALSE);
}

