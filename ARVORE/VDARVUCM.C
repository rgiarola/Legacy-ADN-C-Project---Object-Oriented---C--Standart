#include<INCVIDEO.H>

INT2 VIDEO_ARVORE_mouseumclick(VIDEO_ARVORE_ESTRUTURA **arvore,
                              VIDEO_NUCLEO_SERV      **param)
{
 if (VIDEO_ARVORE_aborta_arvore(arvore,param))
    return(TRUE);
 if (VIDEO_ARVORE_setas_mouse(arvore,param))
    return(TRUE);
 VIDEO_ARVORE_seleciona_mouse(arvore,param);
 return(TRUE);
}
