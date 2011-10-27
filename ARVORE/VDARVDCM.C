#include<INCVIDEO.H>

INT2 VIDEO_ARVORE_mousedoisclick(VIDEO_ARVORE_ESTRUTURA **arvore,
                              VIDEO_NUCLEO_SERV      **param)
{
 INT2 ret;

 if (VIDEO_ARVORE_aborta_arvore(arvore,param))
    return(TRUE);
 if (VIDEO_ARVORE_setas_mouse(arvore,param))
    return(TRUE);
 if (VIDEO_ARVORE_seleciona_mouse(arvore,param))
    return(VIDEO_ARVORE_seleciona(arvore,param));
 return(TRUE);
}
